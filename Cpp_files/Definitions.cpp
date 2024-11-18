#include <stdio.h>
#include <string.h>
#include "Definitions.h"
#include "SubFunctions.h"
#include "Tree.h"

void MakeDefinition(struct Tree* tree) {
    strcpy((tree -> root) -> definition, "Def is: ");

    RecursionDef(tree -> root -> right, tree -> root);
    RecursionDef(tree -> root -> left, tree -> root);
}

void RecursionDef(struct Node* node, struct Node* parent) {
    
    if(node) {
        char* parent_def = parent -> definition;

        memcpy(node -> definition, parent_def, strlen(parent_def));

        char* new_def = node -> definition + strlen(parent_def);
        *new_def = ' ';

        if(parent -> left == node) {
            memcpy(new_def + 1, "NOT ", 4);
            new_def = new_def + 4;
        } 

        memcpy(new_def + 1, parent -> data, strlen(parent -> data));
        *(new_def + 1 + strlen(parent -> data)) = '\0'; 

        printf("%s - %s\n", node -> data, node -> definition);
        RecursionDef(node -> right, node);
        RecursionDef(node -> left, node);
    }
}

void CompareDef(struct Tree* tree) {
    char word1[len_quality] = {};
    char word2[len_quality] = {};

    printf("Enter first word:\n");
    gets(word1);

    printf("Enter second word:\n");
    gets(word2);

    char* def1 = FindDef(word1, tree -> root);
    char* def2 = FindDef(word2, tree -> root);

    if(def1 && def2) {
        PrintDifference(def1, def2);
    } else {
        printf("One of the words doesn`t exist in tree!\n");
    }

}

void PrintDifference(char* def1, char* def2) {
    char qual1[len_quality] = {};
    char qual2[len_quality] = {};

    def1 += def_is;
    def2 += def_is;

    sscanf(def1, "%s", qual1);
    sscanf(def2, "%s", qual2);

    printf("Words are equal in: ");
    while(!mystricmp(qual1, qual2)) {

        printf("%s ", qual1);

        def1 += strlen(qual1) + 1;
        def2 += strlen(qual2) + 1;

        sscanf(def1, "%s", qual1);
        sscanf(def2, "%s", qual2);

    }
    printf("\n");

    sscanf(def1, "%s", qual1);
    sscanf(def2, "%s", qual2);

    printf("Words are different in: ");
    if(!mystricmp(qual1, "NOT")) {
        printf("%s", qual2);
    } else if(!mystricmp(qual2, "NOT")) {
        printf("%s", qual1);
    } 


}

char* FindDef(char* word, struct Node* node) {
    if(node) {
        if(!mystricmp(word, node -> data)) {

            return node -> definition;

        } else {

            if(FindDef(word, node -> left) != NULL) {
                return FindDef(word, node -> left);
            }
            if(FindDef(word, node -> right) != NULL) {
                return FindDef(word, node-> right);
            }

        }
    } 

    return NULL;
}