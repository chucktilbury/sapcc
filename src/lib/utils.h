#ifndef _UTILS_H
#define _UTILS_H

#include "ptrlst.h"
#include "strs.h"
#include <stdbool.h>

typedef struct pattern_t Pattern;
typedef struct pat_elem_t PatElem;
typedef struct rule_t Rule;

PTRLST_HEADER(str_lst, STR)
PTRLST_HEADER(rule_lst, Rule)
PTRLST_HEADER(pattern_lst, Pattern)
PTRLST_HEADER(pat_elem_lst, PatElem)

#include "list.h"
#include "parser.h"

bool str_in_lst(str_lst_t* lst, STR str);
bool is_a_term(Pstate* state, STR str);
bool is_a_nonterm(Pstate* state, STR str);
STR ast_header_name(STR name);
STR ast_source_name(STR name);
STR ast_lock_name(STR name);
STR parser_header_name(STR name);
STR parser_source_name(STR name);
STR parser_lock_name(STR name);
STR scanner_header_name(STR name);
STR scanner_lock_name(STR name);

#endif /* _UTILS_H */
