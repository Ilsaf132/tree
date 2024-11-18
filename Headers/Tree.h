#ifndef TREE_
#define TREE_

#include "ConstantsAndErrors.h"

typedef char* tree_elem_t;

struct Tree {
    struct Node* root;
    int height; // глубина
};

struct Node {
    struct Node* left;
    struct Node* right;
    tree_elem_t data;
    char definition[len_def];
};

#endif