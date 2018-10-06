
#include <stdint.h>
#include <math.h>

// Return errorcode if expr not satisfied
#define EMNET_PRECONDITION(expr, errorcode) \
    do { \
        if (!(expr)) { \
            return errorcode; \
        } \
    } while (0);

// Return errorcode if expr not satisfied
#define EMNET_POSTCONDITION(expr, errorcode) \
    do { \
        if (!(expr)) { \
            return errorcode; \
        } \
    } while (0);

// Return if expr gives error 
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
    EmNetActivationSoftMax,
    EmNetActivationFunctions,
} EmNetActivationFunction;

static const char *
emnet_activation_function_strs[EmNetActivationFunctions] = {
    "identity",
    "relu",
    "logistic",
    "softmax",
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
    EmNetPostconditionFailed,
    EmNetUnknownError,
    EmNetErrors,
} EmNetError;

static const char *
emnet_error_strs[EmNetErrors] = {
    "OK",
    "SizeMismatch",
    "Uninitialized",
    "Unsupported",
    "Postcondition failed",
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

void
print_array(const float *values, int32_t length) {
    printf("n=%d [", length);
    for (int i=0; i<length; i++) {
        printf("%f,", values[i]);
    }
    printf("]\n");    
} 


static float
emnet_relu(float in) {
    return (in <= 0.0f) ? 0.0f : in; 
}

static float
emnet_expit(float in) {
    return 1.0f / (1.0f + expf(-in));
}

static EmNetError
emnet_softmax(float *input, size_t input_length)
{
    EMNET_PRECONDITION(input, EmNetUninitialized);

    float input_max = -INFINITY;
    for (size_t i = 0; i < input_length; i++) {
        if (input[i] > input_max) {
            input_max = input[i];
        }
    }

    float sum = 0.0f;
    for (size_t i = 0; i < input_length; i++) {
        sum += expf(input[i] - input_max);
    }

    const float offset = input_max + logf(sum);
    for (size_t i = 0; i < input_length; i++) {
        input[i] = expf(input[i] - offset);
    }

    return EmNetOk;
}

int32_t
emnet_argmax(float *values, int32_t values_length) {

    float vmax = -INFINITY;
    int32_t argmax = -1;
    for (int i=0; i<values_length; i++) {
        if (values[i] > vmax) {
            vmax = values[i];
            argmax = i;
        }
    }
    return argmax;
}


static bool
emnet_valid(EmNet *model) {
    bool not_null = model->layers && model->activations1 && model->activations2;
    return not_null;
}

static inline int32_t
emnet_outputs(EmNet *model) {
    return model->layers[model->n_layers-1].n_outputs;
}

// For binary problem, one output, we need to report [ prob(class_0), prob(class_1)]
static inline int32_t
emnet_outputs_proba(EmNet *model) {
    int32_t n_outputs = emnet_outputs(model);
    if (n_outputs == 1) {
        n_outputs = 2;
    }
    return n_outputs;
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
    EMNET_PRECONDITION(in_length >= layer->n_inputs, EmNetSizeMismatch);
    EMNET_PRECONDITION(out_length >= layer->n_outputs, EmNetSizeMismatch);
    EMNET_PRECONDITION(layer->weights, EmNetUninitialized);
    EMNET_PRECONDITION(layer->biases, EmNetUninitialized);

    //printf("weights "); print_array(layer->weights, layer->n_inputs*layer->n_outputs);
    //printf("biases "); print_array(layer->biases, layer->n_outputs);

    // TODO: matrix multiplication should be done in blocks. Ex 2x4*4x2 = 2x2
    // multiply inputs by weights
    for (int o=0; o<layer->n_outputs; o++) {
        float sum = 0.0f;
        for (int i=0; i<layer->n_inputs; i++) {
            const int w_idx = o+(i*layer->n_outputs); // not stored continious
            const float w = layer->weights[w_idx];
            sum += w * in[i];
        }

        out[o] = sum + layer->biases[o];

    }

    // apply activation function
    if (layer->activation == EmNetActivationIdentity) {
        // no-op
    } else if (layer->activation == EmNetActivationReLu) {
        for (int i=0; i<layer->n_outputs; i++) {
            out[i] = emnet_relu(out[i]);
        }
    } else if (layer->activation == EmNetActivationLogistic) {
        for (int i=0; i<layer->n_outputs; i++) {
            out[i] = emnet_expit(out[i]);
        }
    } else if (layer->activation == EmNetActivationSoftMax) {
        emnet_softmax(out, layer->n_outputs);
    } else {
        return EmNetUnsupported;
    }

    //printf("activations "); print_array(out, layer->n_outputs);

    return EmNetOk;
}


// Run inferences. Leaves results in activations2
EmNetError
emnet_infer(EmNet *model, const float *features, int32_t features_length)
{
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

    return EmNetOk;
}

EmNetError
emnet_predict_proba(EmNet *model, const float *features, int32_t features_length,
                                  float *out, int32_t out_length)
{
    EMNET_PRECONDITION(emnet_valid(model), EmNetUninitialized);
    EMNET_PRECONDITION(features, EmNetUninitialized);
    EMNET_PRECONDITION(out, EmNetUninitialized);
    const int32_t n_outputs = emnet_outputs_proba(model);
    EMNET_PRECONDITION(out_length == n_outputs, EmNetSizeMismatch);

    EMNET_CHECK_ERROR(emnet_infer(model, features, features_length));

    float proba_sum = 0.0f;

    if (n_outputs == 2) {
        out[1] = model->activations2[0];
        out[0] = 1.0f - out[1];
        proba_sum = out[0] + out[1];
    } else {
        for (int i=0; i<n_outputs; i++) {
            const float p = model->activations2[i];
            out[i] = p;
            proba_sum += p; 
        }
    }

    EMNET_POSTCONDITION(fabs(proba_sum - 1.0) < 0.001, EmNetPostconditionFailed);

    return EmNetOk;
}


// Return the class, or -EmNetError on failure
int32_t
emnet_predict(EmNet *model, const float *features, int32_t features_length) {

    const EmNetError error = emnet_infer(model, features, features_length);
    if (error != EmNetOk) {
        return -error;
    }

    const int32_t n_outputs = emnet_outputs(model);

    int32_t _class = -EmNetUnknownError;
    if (n_outputs == 1) {
        _class = (model->activations2[0] > 0.5f) ? 1 : 0;
    } else if (n_outputs > 1) {
        _class = emnet_argmax(model->activations2, n_outputs);
    }

    return _class;
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





