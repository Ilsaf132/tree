#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SubFunctions.h"
#include "Definitions.h"
#include "Akinator.h"
#include "GraphDump.h"
#include "Tree.h"

Errors_tree AkinatorProgramm(struct Tree* tree) {
    struct Node* node = tree -> root;
    struct Node* parent = tree -> root;
    int guessed_answ = 0;

    if(!tree -> root) {
        tree -> root = CreateNode();

        printf("Enter first quality:\n");
        scanf("%s", (tree -> root) -> data);

        strcpy(tree -> root -> definition, (tree -> root) -> data);
        return NULL_ROOT;
    }

    while(node != NULL) {
        parent = node;
        Errors_tree answer = AnswerNode(node);
        if(answer == YES_CONST) {

            node = node -> right;
            guessed_answ = 1;

        } else if(answer == NO_CONST) {

            node = node -> left;
            guessed_answ = 0;

        } else {

            printf("Wrong type of answer!\n");
            return PROBLEM_ANSWER;

        }
    }

    Guessed_answer(parent, guessed_answ);
    return ERROR_OK;

}

void AkinatorMain(const char* dump_html_name, struct Tree* tree, const char* file_dump) {
    char choose_option = 0;

    printf("\n\n\n\n\n\n\n");

    while(true) {

        printf("\n\nEnter \"g\" to dump tree, enter \"a\" to play Akinator, enter \"d\" to compare definitions, enter \"e\" to end\n");

        if(!scanf(" %c", &choose_option)) {
            return;
        }

        switch(choose_option) {
            case 'g': {

                FILE* dump_html = fopen(dump_html_name, "w+");
                GraphDump(tree, file_dump, dump_html);
                fclose(dump_html); 
                break;

            } case 'a': {

                AkinatorProgramm(tree);
                break;

            } case 'd': {

                // choose_option = getchar();
                CompareDef(tree);
                break;

            } case 'e': {
                
                return;

            } case '\n': {

                break;

            }  default: {

                printf("No command for this symbol!\n");

            }
        }
    }
}

void Guessed_answer(struct Node* parent, int answer) {
    if(answer) {
        printf("I won!\n");
    } else {
        ClearBuffer();
        
        printf("Who did you wish for?\n");
        parent -> left = CreateNode();
        parent -> right = CreateNode();

        strcpy((parent -> left) -> data, parent -> data);
        gets((parent -> right) -> data);
        
        printf("What %s hasn't and %s has?\n", parent -> data, (parent -> right) -> data);
        gets(parent -> data);

        NewElemDefinition(parent);
    }
}

Errors_tree AnswerNode (struct Node* node) {
    printf("%s?\n", node -> data);
    char ans[LenAnswer] = {};

    scanf("%s", ans);
    while(1) {
        if (!mystricmp(ans, "yes")) {

            return YES_CONST;

        } else if (!mystricmp(ans, "no")) {

            return NO_CONST;

        } else {
            printf("Wrong type of answer! Printf yes or no\n");
        }
        scanf("%s", ans);
    }

    return PROBLEM_ANSWER;
}
