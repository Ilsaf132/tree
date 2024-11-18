#include <stdio.h>
#include "GraphDump.h"
#include "ConstantsAndErrors.h"
#include "Tree.h"
#include "SubFunctions.h"

void ArrowsBtwNodes(struct Node* node, FILE* file_dump) {
    if(node -> left) {

        fprintf(file_dump, "    \"%s\" -> \"%s\"[label = \"NO\", fillcolor = \"red\"]\n", node -> data, (node -> left) -> data);
        ArrowsBtwNodes(node -> left, file_dump);
    }
    if(node -> right) {
        fprintf(file_dump, "    \"%s\" -> \"%s\"[label = \"YES\", fillcolor = \"green\"]\n", node -> data, (node -> right) -> data);
        ArrowsBtwNodes(node -> right, file_dump);
    }
}

void RecursionNode(struct Node* node, FILE* file_dump) {
    if(node -> left) {
        fprintf(file_dump, "    \"%s\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p | %s \" "
                "fillcolor = \"grey\"]\n", (node -> left) -> data, (node -> left) -> data, node -> left, (node -> left) -> definition);
        RecursionNode(node -> left, file_dump);
    }
    if(node -> right) {
        fprintf(file_dump, "   \"%s\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p | %s \" "
                "fillcolor = \"grey\"]\n", (node -> right) -> data, (node -> right) -> data, node -> right, (node -> right) -> definition);

        RecursionNode(node -> right, file_dump);
    }
}

void GraphDump(struct Tree* tree, const char* file_name, FILE* dump_html) {
    FILE* file_dump = fopen(file_name, "w");
    
    fprintf(file_dump, "digraph tree {\n");

    fprintf(file_dump, "    \"%s\" [shape = Mrecord, style = \"filled\", label = \"data = %s | address = %p | %s \" "
            "fillcolor = \"purple\"]\n", (tree -> root) -> data, (tree -> root) -> data, tree -> root, (tree -> root) -> definition);
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
