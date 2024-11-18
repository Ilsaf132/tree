#ifndef COMPARE_DEF_
#define COMPARE_DEF_

void PrintDifference(char* def1, char* def2);
char* FindDef(char* word, struct Node* node);
void MakeDefinition(struct Tree* tree);
void RecursionDef(struct Node* node, struct Node* parent);
void NewElemDefinition(struct Node* parent);
void CompareDef(struct Tree* tree);

#endif 