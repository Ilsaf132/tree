#include <stdio.h>
#include <assert.h>
#include <TXLib.h>
#include "TreeLibrary.h" 
#include "Tree.h"

int main() {
    struct Tree tree = {};
    const char* file_tree = "FileTree.txt";
    const char* file_dump = "Dump.dot";
    const char* dump_html_name = "Dump.html";

    if(CreateTree(&tree, file_tree)) return -1;
    AkinatorMain(dump_html_name, &tree, file_dump);
    CreateFileTree(&tree, file_tree);
    Dtor(tree.root);
}
