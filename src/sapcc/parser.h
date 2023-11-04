#ifndef _PARSER_H
#define _PARSER_H

#include "logger.h"
#include "scanner.h"
#include "util.h"

typedef PtrList NonTermList;
typedef PtrListIter NonTermListIter;

typedef PtrList TermList;
typedef PtrListIter TermListIter;

typedef PtrList RuleList;
typedef PtrListIter RuleListIter;

typedef struct {
    Str* name;
    bool keep;
    int ref;
    int val;
} Terminal;

// Rules to match the non-terminal.
typedef struct {
    StrList* list;
} Rule;

typedef struct {
    Str* name;
    RuleList* list;
    int prec;
    int ref;
    int val;
} NonTerminal;

typedef struct {
    TermList* terminals;
    NonTermList* non_terminals;
    StrList* headers;
    StrList* sources;
} Parser;

void init_parser();
void destroy_parser();
Parser* parser();
void dump_parser();

int get_num_term();
int get_num_nterm();
TermList* get_term_list();
NonTermList* get_nterm_list();

extern CmdLine cmd;


#endif /* _PARSER_H */
