#ifndef GRAPH_DUMP_
#define GRAPH_DUMP_

#include <stdio.h>

void RecursionNode(struct Node* node, FILE* file_dump);
void GraphDump(struct Tree* tree, const char* file_name, FILE* dump_html);
void ArrowsBtwNodes(struct Node* node, FILE* file_dump);

#endif