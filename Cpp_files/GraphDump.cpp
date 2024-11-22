#include <stdio.h>
#include <stdlib.h>
#include "GraphDump.h"
#include "ConstantsAndErrors.h"
#include "Tree.h"
#include "SubFunctions.h"

void ArrowsBtwNodes(struct Node* node, FILE* file_dump) {
    if(node -> left) {

        fprintf(file_dump, "    \"%p\" -> \"%p\"[label = \"NO\", fillcolor = \"red\"]\n", node, node -> left);
        ArrowsBtwNodes(node -> left, file_dump);
    }
    if(node -> right) {
        fprintf(file_dump, "    \"%p\" -> \"%p\"[label = \"YES\", fillcolor = \"green\"]\n", node, node -> right);
        ArrowsBtwNodes(node -> right, file_dump);
    }
}

void RecursionNode(struct Node* node, FILE* file_dump) {
    if(node -> left) {
        fprintf(file_dump, "    \"%p\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p | left = %p | right = %p ]\" "
                "fillcolor = \"grey\"]\n", node -> left, (node -> left) -> data, node -> left, node -> left -> left, node -> left -> right);
        RecursionNode(node -> left, file_dump);
    }
    if(node -> right) {
        fprintf(file_dump, "   \"%p\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p | left = %p | right = %p \" "
                "fillcolor = \"grey\"]\n", node -> right, (node -> right) -> data, node -> right, node -> right -> left, node -> right -> right);

        RecursionNode(node -> right, file_dump);
    }
}

void GraphDump(struct Tree* tree, const char* file_name, FILE* dump_html) {
    FILE* file_dump = fopen(file_name, "w");
    
    fprintf(file_dump, "digraph tree {\n");

    fprintf(file_dump, "    \"%s\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p [ %p | %p ]\""
            "fillcolor = \"purple\"]\n", (tree -> root) -> data, (tree -> root) -> data, tree -> root, tree->root->left, tree->root->right);
    RecursionNode(tree -> root, file_dump);
    ArrowsBtwNodes(tree -> root, file_dump);

    fprintf(file_dump, "}");

    fclose(file_dump);

    static int number_dump = 0;

    MySystem("dot Dump.dot -Tpng -o Graphs\\Dump%02d.png", number_dump);

    if(number_dump == 0) {
        fprintf(dump_html, "<pre>\n");
    }

    fprintf(dump_html, "\n<img src = \"Graphs\\Dump%02d.png\"/>\n", number_dump);
    number_dump++;

}
