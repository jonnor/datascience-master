
#ifndef EXTREE_H

#include <stdint.h>

typedef float ExValue; // TODO: make integer/fixed-point

typedef struct _ExNode {
    int8_t feature;
    ExValue value;
    int8_t left;
    int8_t right;
} ExNode;

typedef struct _ExTree {
    int32_t n_nodes;
    ExNode *nodes;
} ExTree;

// TODO: implement forest
typedef struct _ExForest {
    int32_t n_trees;
    ExTree *trees;
};

int32_t extree_predict(const ExTree *tree, const ExValue *features, int8_t features_length) {
    int32_t node_idx = tree->n_nodes - 1; // root

    while (tree->nodes[node_idx].feature > 0) {
        printf("n %d\n", node_idx);
        const int8_t feature = tree->nodes[node_idx].feature;
        const ExValue value = features[feature];
        node_idx = (value < tree->nodes[node_idx].value) ? tree->nodes[node_idx].left : tree->nodes[node_idx].right;
    }
    return tree->nodes[node_idx].value;
}

#endif // EXTREE_H
