#ifndef AKINATOR_
#define AKINATOR_

#include "ConstantsAndErrors.h"
#include <stdio.h>

#define TAB(tab) for(int i = 0; i < tab; ++i) {\
                fprintf(fp, "\t");\
            }

Errors_tree AkinatorProgramm(struct Tree* tree);
Errors_tree CreateTree(struct Tree* tree, const char* file_tree);
struct Node* FullingTreeStart(struct Node* node, FILE* fp); 
Errors_tree CreateFileTree(struct Tree* tree, const char* file_tree);
void FileFulling(struct Node* node, FILE* fp, int tab);
void Dtor(struct Node* node);
struct Node* CreateNode();
Errors_tree AnswerNode (struct Node* node);
struct Node* CreateRoot(char* quality);

#endif