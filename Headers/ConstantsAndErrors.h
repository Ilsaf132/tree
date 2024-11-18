#ifndef CONST_
#define CONST_

const int len_answer = 10;
const int len_quality = 50;
const int len_def = 250;
const int def_is = 8;

enum Errors_tree {
    NULL_ROOT = 0,
    ERROR_OK = 0,
    YES_CONST,
    NO_CONST,
    PROBLEM_ANSWER,
    ERROR_CREATE,
    NULL_TREE_ADDRESS,
    ERROR_FILE,
};

#endif 