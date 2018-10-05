
#include <stdint.h>

// TODO: implement elu
// TODO: implement SeLu for SNN
typedef enum _EmNetActivationFunction {
    EmNetActivationIdentity,
    EmNetActivationReLu,
} EmNetActivationFunction;

typedef struct _EmNetLayer {
    int32_t n_outputs;
    int32_t n_inputs;
    float *weights;
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
} EmNetError;

static float
emnet_relu(float in) {
    return (in <= 0) ? 0 : in; 
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
    if (layer->n_inputs < in_length) {
        return EmNetSizeMismatch;
    }

    if (layer->n_outputs < out_length) {
        return EmNetSizeMismatch;
    }

    // TODO: matrix multiplication should be done in blocks. Ex 2x4*4x2 = 2x2
    // multiply inputs by weights
    for (int o=0; o<layer->n_outputs; o++) {
        float sum = 0.0f;
        for (int i=0; i<layer->n_inputs; i++) {
            const float w = layer->weights[(o*layer->n_outputs)+i];
            sum += w * in[i];
        }

        // PERF: compute activation right here?
        out[o] = sum;
    }

    // apply activation function
    if (layer->activation == EmNetActivationReLu) {
        for (int i=0; i<out_length; i++) {
            out[i] = emnet_relu(out[i]);
        }
    } else if (layer->activation == EmNetActivationIdentity) {
        // no-op
    } else {
        return EmNetUnsupported; // error
    }

    return EmNetOk;
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

EmNetError
emnet_infer(EmNet *model, const float *features, int32_t features_length)
{
    if (model->n_layers < 3) {
        return EmNetUnsupported;
    }

    const size_t buffer_length = model->activations_length; 
    float *buffer1 = model->activations1;
    float *buffer2 = model->activations2;

    const int32_t buffer_size_needed = emnet_find_largest_layer(model);
    if (buffer_length < buffer_size_needed) {
        return EmNetSizeMismatch;
    }

    // Input layer
    emnet_layer_forward(&model->layers[0], features, features_length, buffer2, buffer_length);

    // Hidden layers
    for (int i=1; i<model->n_layers-1; i++) {
        const EmNetLayer *layer = &model->layers[i];
        // PERF: avoid copying, swap buffers instead
        emnet_layer_forward(layer, buffer1, buffer_length, buffer2, buffer_length);
        for (int i=0; i<buffer_length; i++) {
            buffer1[i] = buffer2[i];
        }
    }

    // Output layer
    emnet_layer_forward(&model->layers[model->n_layers-1], buffer1, buffer_length, buffer2, buffer_length);

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
    const int32_t winner = emnet_argmax(model->activations2, n_outputs);
    return winner;
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





