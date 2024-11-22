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
    char definition[LenDef];
};

struct Node* CreateRoot(char* quality);
Errors_tree CreateTree(struct Tree* tree, const char* file_tree);
struct Node* FullingTreeStart(struct Node* node, FILE* fp); 
Errors_tree CreateFileTree(struct Tree* tree, const char* file_tree);
void FileFulling(struct Node* node, FILE* fp, int tab);
void Dtor(struct Node* node);
struct Node* CreateNode();

#endif