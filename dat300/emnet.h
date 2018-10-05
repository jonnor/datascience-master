
#include <stdint.h>
#include <math.h>

#define EMNET_PRECONDITION(expr, errorcode) \
    do { \
        if (!(expr)) { \
            return errorcode; \
        } \
    } while (0);

#define EMNET_CHECK_ERROR(expr) \
    do { \
        const EmNetError _e = (expr); \
        if (_e != EmNetOk) { \
            return _e; \
        } \
    } while (0);


// TODO: implement sigmoid
// TODO: implement tanh
// TODO: implement elu
// TODO: implement SeLu for SNN
typedef enum _EmNetActivationFunction {
    EmNetActivationIdentity = 0,
    EmNetActivationReLu,
    EmNetActivationLogistic,
    EmNetActivationFunctions,
} EmNetActivationFunction;

static const char *
emnet_activation_function_strs[EmNetActivationFunctions] = {
    "identity",
    "relu",
    "logistic",
};

typedef struct _EmNetLayer {
    int32_t n_outputs;
    int32_t n_inputs;
    float *weights;
    float *biases;
    EmNetActivationFunction activation;
} EmNetLayer;

typedef struct _EmNet {
    // Layers of the neural network
    int32_t n_layers;
    EmNetLayer *layers;
    // Buffers for storing activations
    float *activations1;
    float *activations2;
    int32_t activations_length;
} EmNet;

typedef enum _EmNetError {
    EmNetOk = 0,
    EmNetSizeMismatch,
    EmNetUnsupported,
    EmNetUninitialized,
    EmNetUnknownError,
    EmNetErrors,
} EmNetError;

static const char *
emnet_error_strs[EmNetErrors] = {
    "OK",
    "SizeMismatch",
    "Uninitialized",
    "Unsupported",
    "Unknown error",
};

bool
emnet_error_valid(EmNetError e) {
    return (e >= EmNetOk && e < EmNetErrors);
}

const char *
emnet_strerr(EmNetError e) {
    if (emnet_error_valid(e)) {
        return emnet_error_strs[e];
    } else {
        return NULL;
    }
}


static float
emnet_relu(float in) {
    return (in <= 0.0f) ? 0.0f : in; 
}

static float
emnet_expit(float in) {
    return 1.0f / (1.0f + expf(-in));
}

int32_t
emnet_argmax(float *values, int32_t values_length) {
    int32_t ret = -1;
    for (int i=0; i<values_length; i++) {
        if (values[i] > ret) {
            ret = values[i];
        }
    }
    return ret;
}

void
print_array(const float *values, int32_t length) {
    printf("n=%d [", length);
    for (int i=0; i<length; i++) {
        printf("%f,", values[i]);
    }
    printf("]\n");    
} 


bool
emnet_valid(EmNet *model) {
    bool not_null = model->layers && model->activations1 && model->activations2;
    return not_null;
}

// Calculate size of activation value arrays
static int32_t
emnet_find_largest_layer(EmNet *model) {
    int32_t largest = -1;
    for (int i=0; i<model->n_layers; i++) {
        if (model->layers[i].n_inputs > largest) {
            largest = model->layers[i].n_inputs;
        }
        if (model->layers[i].n_outputs > largest) {
            largest = model->layers[i].n_outputs;
        }
    }
    return largest;
}

// CMSIS-NN tricks
// - fixed-point math
// - quantize to 8 or 16 bit (q7,q15)
// - block-based matrix and vector multiplication
// - weight reordering to match multiplication blocks
// CNN
// - partial im2col, reordering image to match convolution kernel (and size).
// - split x-y pooling. in-place. 4.5x speedup
// Activations
// - SIMD relu on signbit
// CIFAR-10, 80% accuracy, 100ms. 87KB weights, 55KB activations 

// MobileNets
// depthwise-separable convolution, for multiple (color) channels
//
// Strassen matrix multiplication
// Winograd filter-based convolution, 16mul instead of 36. 2-3x speedup on GPU
// "Fast algorithms for convolutional neural networks"
// https://arxiv.org/abs/1509.09308
//
// Convolutional Kernel Networks
// https://papers.nips.cc/paper/5348-convolutional-kernel-networks.pdf
// Approximation of CNN with Gaussian kernels, on unsupervised feature kernels
// reached state-of-art in MINST/CIFAR-10 with linear SVM classifier
// scattering transform also did well


EmNetError
emnet_layer_forward(const EmNetLayer *layer,
                    const float *in, int32_t in_length,
                    float *out, int32_t out_length)
{
    printf("forward. in=%d out=%d n_in=%d, n_out=%d\n",
                    in_length, out_length, layer->n_inputs, layer->n_outputs);

    EMNET_PRECONDITION(in_length >= layer->n_inputs, EmNetSizeMismatch);
    EMNET_PRECONDITION(out_length >= layer->n_outputs, EmNetSizeMismatch);
    EMNET_PRECONDITION(layer->weights, EmNetUninitialized);
    EMNET_PRECONDITION(layer->biases, EmNetUninitialized);

    printf("weights "); print_array(layer->weights, layer->n_inputs*layer->n_outputs);
    printf("biases "); print_array(layer->biases, layer->n_outputs);

    // TODO: matrix multiplication should be done in blocks. Ex 2x4*4x2 = 2x2
    // multiply inputs by weights
    for (int o=0; o<layer->n_outputs; o++) {
        float sum = 0.0f;
        for (int i=0; i<layer->n_inputs; i++) {
            const int w_idx = (o*layer->n_inputs)+i;
            const float w = layer->weights[w_idx];
            sum += w * in[i];
            printf("(%d,%d) idx=%d, w=%f, in=%f\n",
                    o,i, w_idx, w, in[i]);
        }

        out[o] = sum + layer->biases[o];
        // PERF: compute activation right here?
        printf("sum=%f out=%d\n", sum, out[o]);
    }

    // apply activation function
    if (layer->activation == EmNetActivationIdentity) {
        // no-op
    } else if (layer->activation == EmNetActivationReLu) {
        for (int i=0; i<out_length; i++) {
            out[i] = emnet_relu(out[i]);
        }
    } else if (layer->activation == EmNetActivationLogistic) {
        for (int i=0; i<out_length; i++) {
            out[i] = emnet_expit(out[i]);
        }
    } else {
        return EmNetUnsupported;
    }

    return EmNetOk;
}

EmNetError
emnet_infer(EmNet *model, const float *features, int32_t features_length)
{
    printf("features: "); print_array(features, features_length);
    printf("n_inputs: %d\n", model->layers[0].n_inputs);
    printf("activation buffer: %d %d\n", model->activations_length, emnet_find_largest_layer(model));

    EMNET_PRECONDITION(emnet_valid(model), EmNetUninitialized);
    EMNET_PRECONDITION(model->n_layers >= 2, EmNetUnsupported);
    EMNET_PRECONDITION(features_length == model->layers[0].n_inputs, EmNetSizeMismatch);
    EMNET_PRECONDITION(model->activations_length >= emnet_find_largest_layer(model), EmNetSizeMismatch);

    const int32_t buffer_length = model->activations_length; 
    float *buffer1 = model->activations1;
    float *buffer2 = model->activations2;

    // Input layer
    EMNET_CHECK_ERROR(emnet_layer_forward(&model->layers[0], features,
                        features_length, buffer1, buffer_length));

    // Hidden layers
    for (int i=1; i<model->n_layers-1; i++) {
        const EmNetLayer *layer = &model->layers[i];
        // PERF: avoid copying, swap buffers instead
        EMNET_CHECK_ERROR(emnet_layer_forward(layer, buffer1, buffer_length, buffer2, buffer_length));
        for (int i=0; i<buffer_length; i++) {
            buffer1[i] = buffer2[i];
        }
    }

    // Output layer
    EMNET_CHECK_ERROR(emnet_layer_forward(&model->layers[model->n_layers-1],
                        buffer1, buffer_length, buffer2, buffer_length));

    // FIXME: do something prettier with output than leaving it in activations2...

    return EmNetOk;
}

// Return the class, or -EmNetError on failure
int32_t
emnet_predict(EmNet *model, const float *features, int32_t features_length) {

    const EmNetError error = emnet_infer(model, features, features_length);
    if (error != EmNetOk) {
        return -error;
    }

    const int32_t n_outputs = model->layers[model->n_layers-1].n_outputs;

    printf("outputs: "); print_array(model->activations2, n_outputs);

    if (n_outputs == 1) {
        return model->activations2[0] > 0.5;
    } else if (n_outputs > 1) {
        return emnet_argmax(model->activations2, n_outputs);
    } else {
        return -EmNetUnknownError;
    }

}




#if 0 
EmNetError
emnet_parse_csv_line(const char *buffer, float *values, int32_t values_length) {
        
    int field_no = 0;
    const char seps[] = ",;";
    char *token = strtok(buffer, seps);

    while (token != NULL)
    {
        long value;
        sscanf(token, "%ld", &value);

        if (field_no >= values_length) {
            return EmNetSizeMismatch;
        }

        values[field_no] = value; 
        field_no++;
        token = strtok(NULL, seps);
    }

    return EmNetOk;
}

#endif





