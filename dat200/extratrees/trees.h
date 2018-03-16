
#ifndef EXTREE_H

#include <stdint.h>

typedef float ExValue; // TODO: make integer/fixed-point

typedef struct _ExNode {
    int8_t feature;
    ExValue value;
    int16_t left;
    int16_t right;
} ExNode;


typedef struct _ExForest {
    int32_t n_nodes;
    ExNode *nodes;

    int32_t n_trees;
    int32_t *tree_roots;

    // int8_t n_features;
    // int8_t n_classes;
} ExForest;


#ifndef EX_MAX_CLASSES
#define EX_MAX_CLASSES 10
#endif

static int32_t
extree_predict(const ExForest *forest, int32_t tree_root, const ExValue *features, int8_t features_length) {
    int32_t node_idx = tree_root;

    while (forest->nodes[node_idx].feature > 0) {
        //printf("n %d\n", node_idx);
        const int8_t feature = forest->nodes[node_idx].feature;
        const ExValue value = features[feature];
        node_idx = (value < forest->nodes[node_idx].value) ? forest->nodes[node_idx].left : forest->nodes[node_idx].right;
    }
    return forest->nodes[node_idx].value;
}

int32_t
exforest_predict(const ExForest *forest, const ExValue *features, int8_t features_length) {

    //printf("features %d\n", features_length);
    //printf("trees %d\n", forest->n_trees);

    // FIXME: check if number of tree features is bigger than provided
    // FIXME: check if number of classes is bigger than MAX_CLASSES, error
 
    int32_t votes[EX_MAX_CLASSES] = {0};
    for (int32_t i=0; i<forest->n_trees; i++) {
        const int32_t _class = extree_predict(forest, forest->tree_roots[i], features, features_length);
        //printf("pred[%d]: %d\n", i, _class);
        if (_class >= 0) {
            votes[_class] += 1;
        }
    }
    
    int32_t most_voted_class = -1;
    int32_t most_voted_votes = 0;
    for (int32_t i=0; i<EX_MAX_CLASSES; i++) {
        //printf("votes[%d]: %d\n", i, votes[i]);
        if (votes[i] > most_voted_votes) {
            most_voted_class = i;
            most_voted_votes = votes[i];
        }
    }

    return most_voted_class;
}

#endif // EXTREE_H
