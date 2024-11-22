#include <stdio.h>
#include <string.h>
#include "Definitions.h"
#include "SubFunctions.h"
#include "Tree.h"

void MakeDefinition(struct Tree* tree) {
    strcpy((tree -> root) -> definition, " ");

    RecursionDef(tree -> root -> right, tree -> root, 0);
    RecursionDef(tree -> root -> left, tree -> root, 0);
}

void NewElemDefinition(struct Node* parent) {
    struct Node* node_right = parent -> right;
    struct Node* node_left = parent -> left;
    int new_len_def = strlen(parent -> definition); 
    const size_t not_strlen = strlen(" NOT ");

    memcpy(node_right -> definition, parent -> definition, new_len_def);
    memcpy(node_left -> definition, parent -> definition, new_len_def);

    memcpy(node_right -> definition + new_len_def, " ", 1);
    memcpy(node_left -> definition + new_len_def, " NOT ", not_strlen);

    memcpy(node_right -> definition + new_len_def + 1, parent -> data, strlen(parent -> data));
    memcpy(node_left -> definition + new_len_def + not_strlen, parent -> data, strlen(parent -> data));

    int final_len_r = new_len_def + 1 + strlen(parent -> data);
    int final_len_l = new_len_def + not_strlen + strlen(parent -> data);

    memcpy(node_right -> definition + final_len_r, "\0", 1);
    memcpy(node_left -> definition + final_len_l, "\0", 1);

    printf("%s: %s\n", node_left -> data, node_left -> definition);
    printf("%s: %s\n", node_right -> data, node_right -> definition);
}

void RecursionDef(struct Node* node, struct Node* parent, int root_def) {
    
    if(node) {
        
        char* parent_def = parent -> definition;

        memcpy(node -> definition, parent_def, strlen(parent_def));

        char* new_def = node -> definition + strlen(parent_def);
        if(root_def) {
            *new_def = ',';
            new_def++;
            *new_def = ' ';
        } else {
            root_def++;
            new_def--;
        }

        if(parent -> left == node) {
            memcpy(new_def + 1, "NOT ", strlen("NOT "));
            new_def = new_def + strlen("NOT ");
        } 

        memcpy(new_def + 1, parent -> data, strlen(parent -> data));
        *(new_def + 1 + strlen(parent -> data)) = '\0';

        printf("%s - %s\n", node -> data, node -> definition);
        
        RecursionDef(node -> right, node, 1);
        RecursionDef(node -> left, node, 1);
    }
}

void CompareDef(struct Tree* tree) {
    char word1[LenQuality] = {};
    char word2[LenQuality] = {};

    printf("Enter first word:\n");
    scanf(" %s", word1);
    // gets(word1);

    printf("Enter second word:\n");
    scanf(" %s", word2);
    // gets(word2);

    char* def1 = FindDef(word1, tree -> root);
    char* def2 = FindDef(word2, tree -> root);

    if(def1 && def2) {
        PrintDifference(def1, def2);
    } else {
        printf("One of the words doesn`t exist in tree!\n");
    }

}

void PrintDifference(char* def1, char* def2) {

    printf("Words are equal in: ");
    while(*def1 == *def2 && *def1 != '\0') {

        printf("%c", *def1);

        def1++;
        def2++;

    }
    printf("\n");

    printf("Words are different since:\n");
    printf("%s\n", def1);
    printf("%s\n", def2);


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