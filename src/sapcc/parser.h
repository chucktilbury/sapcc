#ifndef _PARSER_H
#define _PARSER_H

#include <stdbool.h>

#include "fileio.h"
#include "strs.h"
#include "utils.h"

struct pat_elem_t {
    Str str;
    bool is_terminal;
};

struct pattern_t {
    // str_lst_t* lst;
    pat_elem_lst_t* elems;
    Str code; // C code to run upon a pattern match
};

struct rule_t {
    Str name;
    int cols;
    int rows;
    bool is_recursive;
    bool has_nonterms;
    pattern_lst_t* patterns;
};

typedef struct {

    bool finished;
    int verbo;

    // raw names of output files as given by directives
    Str name;
    Str prefix;

    // string lists that will be copied as source code to the output,
    // as given by directives
    str_lst_t* code;

    // the raw rules as presented in the grammar
    rule_lst_t* rules;

    // list of all terminal and non-terminal words
    str_lst_t* terminals;
    str_lst_t* non_terminals;
} Pstate;

Pstate* parse_input(const char* fname);

#endif /* _PARSER_H */
