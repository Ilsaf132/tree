#ifndef AKINATOR_
#define AKINATOR_

#include "ConstantsAndErrors.h"
#include <stdio.h>

Errors_tree AkinatorProgramm(struct Tree* tree);
void AkinatorMain(const char* dump_html_name, struct Tree* tree, const char* file_dump); 
Errors_tree AnswerNode(struct Node* node);
void Guessed_answer(struct Node* parent, int answer);

#endif