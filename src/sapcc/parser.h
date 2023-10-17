#ifndef _PARSER_H
#define _PARSER_H

#include "scanner.h"
#include "logger.h"
#include "util.h"

typedef PtrList NonTermList;
typedef PtrList TermList;
typedef PtrList RuleList;

typedef struct {
    Str* name;
    bool keep;
    int ref;
} Terminal;

// Rules to match the non-terminal.
typedef struct {
    StrList* list;
    Str* match;
} Rule;

typedef struct {
    Str* name;
    RuleList* list;
    Str* pre_match;
    Str* post_match;
    int ref;
} NonTerminal;

typedef struct {
    TermList* terminals;
    NonTermList* non_terminals;
    StrList* headers;
    StrList* sources;
} Parser;

void init_parser();
void destroy_parser();
int parser();
void dump_parser();

int get_num_term();
int get_num_nterm();

extern CmdLine cmd;


#endif /* _PARSER_H */
