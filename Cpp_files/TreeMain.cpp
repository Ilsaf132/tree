#include <stdio.h>
#include <assert.h>
#include <TXLib.h>
#include "TreeLibrary.h" 

int main() {
    struct Tree tree = {};
    const char* file_tree = "FileTree.txt";
    const char* file_dump = "Dump.dot";
    const char* dump_html_name = "Dump.html";
    FILE* dump_html = fopen(dump_html_name, "w+");

    if(CreateTree(&tree, file_tree)) return -1;
    char choose_option = 0;
    char n_char = 0;

    printf("\n\n\n\nEnter \"g\" to dump tree, enter \"a\" to play Akinator, enter \"d\" to compare definitions, enter \"e\" to end\n");
    choose_option = getchar();
    n_char = getchar();

    while(1) {

        if (choose_option == 'g') {

            GraphDump(&tree, file_dump, dump_html);

        } else if (choose_option == 'a') {

            AkinatorProgramm(&tree);

        } else if (choose_option == 'd') {

            CompareDef(&tree);

        } else if (choose_option == 'e') {
            
            break;

        } else {

            printf("No command for this symbol!\n");

        }

        printf("\n\nEnter \"g\" to dump tree, enter \"a\" to play Akinator, enter \"d\" to compare definitions, enter \"e\" to end\n");
        choose_option = getchar();
        n_char = getchar();
        
    }
    
    CreateFileTree(&tree, file_tree);

    fclose(dump_html); 
    Dtor(tree.root);
}
