#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SubFunctions.h"

void MySystem(const char* str, int number_dump)
{
    char command_dot[52] = "";

    sprintf(command_dot, str, number_dump);

    system(command_dot);
}

int mystricmp(const char* word1, const char* word2) {

    while (*word1 && toupper(*word2) == toupper(*word1)){
        word1++;
        word2++;
    }
    return *word1 - *word2;

}

const char* mystrchr(const char* str, int symb) {
    if (!strchr(str, symb)) {

        while(*str == 9 || *str == 32) {
            str++;
        }
        return str;

    } 
    return strchr(str, symb) + 1;
}
