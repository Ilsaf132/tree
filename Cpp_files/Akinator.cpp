#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SubFunctions.h"
#include "Definitions.h"
#include "Akinator.h"
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

    if(guessed_answ) {
        printf("I won!\n");
    } else {
        printf("Who did you wish for?\n");
        parent -> left = CreateNode();
        parent -> right = CreateNode();

        strcpy((parent -> left) -> data, parent -> data);
        scanf("%s", (parent -> right) -> data);

        printf("What`s the difference between %s and %s?\n", parent -> data, (parent -> right) -> data);
        scanf("%s", parent -> data);

        NewElemDefinition(parent);

    }
    return ERROR_OK;

}

Errors_tree CreateFileTree(struct Tree* tree, const char* file_tree) {
    FILE* fp = fopen(file_tree, "w");

    if(fp) {

        FileFulling(tree -> root, fp, 0);

    } else {
        printf("Problem with opening file to write!\n");
        return ERROR_FILE;
    }
    fclose(fp);

    return ERROR_OK;
}

void FileFulling(struct Node* node, FILE* fp, int tab) {
    
    if(node) {
        TAB(tab)
        fprintf(fp, "{\n");

        TAB(tab + 1);
        fprintf(fp, "\"%s\"\n", node -> data);

        FileFulling(node -> right, fp, tab + 1);
        FileFulling(node -> left, fp, tab + 1);

        TAB(tab)
        fprintf(fp, "}\n");
    }
    
}

void NewElemDefinition(struct Node* parent) {
    struct Node* node_right = parent -> right;
    struct Node* node_left = parent -> left;
    int new_len_def = strlen(parent -> definition); 

    memcpy(node_right -> definition, parent -> definition, new_len_def);
    memcpy(node_left -> definition, parent -> definition, new_len_def);

    memcpy(node_right -> definition + new_len_def, " ", 1);
    memcpy(node_left -> definition + new_len_def, " NOT ", 5);

    memcpy(node_right -> definition + new_len_def + 1, parent -> data, strlen(parent -> data));
    memcpy(node_left -> definition + new_len_def + 5, parent -> data, strlen(parent -> data));

    int final_len_r = new_len_def + 1 + strlen(parent -> data);
    int final_len_l = new_len_def + 5 + strlen(parent -> data);

    memcpy(node_right -> definition + final_len_r, "\0", 1);
    memcpy(node_left -> definition + final_len_l, "\0", 1);

    printf("%s: %s\n", node_left -> data, node_left -> definition);
    printf("%s: %s\n", node_right -> data, node_right -> definition);
}

struct Node* FullingTreeStart(struct Node* node, FILE* fp) {
    char quality_bracket[len_quality] = {};
    char quality[len_quality] = {};

    if(fgets(quality_bracket, len_quality, fp) == NULL) {
        printf("gde-to proeb\n");
        return NULL;
    } 
    printf("word: %s\n", quality_bracket);

    sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality);
    printf("word 2: %s\n\n", quality);

    if(mystricmp(quality, "{\n") && mystricmp(quality, "}\n")) {
        node = CreateNode();
        strcpy(node -> data, quality);

        if(fgets(quality_bracket, len_quality, fp) == NULL) {
            printf("gde-to proeb\n");
            return NULL;
        } 
        sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality);
        printf("after word %s: %s\n", node -> data, quality);
    }

    if(!mystricmp(quality, "{\n")) {

        node -> right = FullingTreeStart(node -> right, fp);

    } else if(!mystricmp(quality, "}\n")) {

        return node;

    }

    if(fgets(quality_bracket, len_quality, fp) == NULL) {
        printf("gde-to proeb\n");
        return NULL;
    } 
    sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality); // {
    printf("left side for %s: %s\n", node -> data, quality);

    node -> left = FullingTreeStart(node -> left, fp);

    if(fgets(quality_bracket, len_quality, fp) == NULL) {
        printf("gde-to proeb\n");
        return NULL;
    } 
    sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality); // }
    
    printf("last brack to %s: %s\n", node -> data, quality);
    return node;
    
}

struct Node* CreateRoot(char* quality) {
    struct Node* root = CreateNode();
    root -> data = quality;

    return root;
}

Errors_tree AnswerNode (struct Node* node) {
    printf("%s?\n", node -> data);
    char ans[len_answer] = {};

    scanf("%s", ans);

    if (!mystricmp(ans, "yes")) {

        return YES_CONST;

    } else if (!mystricmp(ans, "no")) {

        return NO_CONST;

    }

    return PROBLEM_ANSWER;
}

Errors_tree CreateTree(struct Tree* tree, const char* file_tree) {
    if(tree == NULL) {
        printf("NULL tree address!\n");
        return NULL_TREE_ADDRESS;
    }

    tree -> height = 0;

    FILE* fp = fopen(file_tree, "r");

    if (fp) {
        printf("OPENED!\n");

        char quality[len_quality] = {};
        fgets(quality, len_quality, fp);
        printf("kavuchka: %s\n", quality);
        printf("len quality: %d\n", strlen(quality));

        if(!mystricmp(quality, "{\n")) {
            
            printf("with bracket!\n");

        } else {

            printf("Wrong format of enter!\n");
            return ERROR_CREATE;

        }
        printf("address root: %p\n", tree -> root);

        tree -> root = FullingTreeStart(tree -> root, fp);

        printf("Root create is done!\n");

        MakeDefinition(tree);
    }

    fclose(fp);

    return ERROR_OK;    
}

struct Node* CreateNode() {
    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    node -> data = (char*) calloc(len_quality, sizeof(char));

    return node;
}

void Dtor(struct Node* node) {
    if(!node) {
        return;
    }
    Dtor(node -> right);
    Dtor(node -> left);
    free(node -> data);
    free(node);
    node = NULL;
}

