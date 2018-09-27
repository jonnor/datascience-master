

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
    int32_t n_layers;
    EmNetLayer *layers;
} EmNet;

static float
emnet_relu(float in) {
    return (in <= 0) ? 0 : in; 
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

// memory needed for largest inputs,output pair
int8_t
emnet_layer_forward(EmNetLayer *layer,
                    float *in, int32_t in_length,
                    float *out, int32_t out_length)
{
    // TODO: matrix multiplication should be done in blocks. Ex 2x4*4x2 = 2x2
    // multiply inputs by weights
    for (int o=0; o<out_length; o++) {
        float sum = 0.0f;
        for (int i=0; i<in_length; i++) {
            const float w = layer->weights[o][i];
            sum += w * in[i];
        }

        // TODO: compute activation right here?
        out[0] = sum;
    }

    // apply activation function
    if (layer->activation == EmNetActivationReLu) {
        for (int i=0; i<out_length; i++) {
            out[i] = emnet_relu(out[i]);
        }
    } else if (layer->activation == EmNetActivationIdentity) {
        // no-op
    } else {
        return -1; // error
    }
}


int8_t
emnet_infer(EmNet *model, float *features, int32_t features_length,
            float *out, int32_t out_length)
{
    for (int l; l<model->n_layers; l)
}

/*
int32_t
emnet_predict_binary(EmNet *model, float features) {
    emnet_infer();
}
*/

float wei
