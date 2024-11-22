#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"
#include "SubFunctions.h"
#include "Definitions.h"

#define TAB(tab) for(int i = 0; i < tab; ++i) {\
                fprintf(fp, "\t");\
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

struct Node* FullingTreeStart(struct Node* node, FILE* fp) {
    char quality_bracket[LenQuality] = {};
    char quality[LenQuality] = {};

    if(fgets(quality_bracket, LenQuality, fp) == NULL) {
        printf("gde-to proeb\n");
        return NULL;
    } 
    printf("word: %s\n", quality_bracket);

    sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality);
    printf("word 2: %s\n\n", quality);

    if(mystricmp(quality, "{\n") && mystricmp(quality, "}\n")) {
    
        node = CreateNode();
        strcpy(node -> data, quality);

        if(fgets(quality_bracket, LenQuality, fp) == NULL) {
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

    if(fgets(quality_bracket, LenQuality, fp) == NULL) {
        printf("gde-to proeb\n");
        return NULL;
    } 
    sscanf(mystrchr(quality_bracket, '\"'), "%[^\"]", quality); // {
    printf("left side for %s: %s\n", node -> data, quality);

    node -> left = FullingTreeStart(node -> left, fp);

    if(fgets(quality_bracket, LenQuality, fp) == NULL) {
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

Errors_tree CreateTree(struct Tree* tree, const char* file_tree) {
    if(tree == NULL) {
        printf("NULL tree address!\n");
        return NULL_TREE_ADDRESS;
    }

    tree -> height = 0;

    FILE* fp = fopen(file_tree, "r");

    if (fp) {
        printf("OPENED!\n");

        char quality[LenQuality] = {};
        fgets(quality, LenQuality, fp);
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
    node -> data = (char*) calloc(LenQuality, sizeof(char));

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
