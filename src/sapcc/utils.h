#ifndef _UTILS_H
#define _UTILS_H

#include "strs.h"
#include <stdbool.h>

typedef struct pattern_t Pattern;
typedef struct pat_elem_t PatElem;
typedef struct rule_t Rule;

PTRLST_HEADER(str_lst, Str)
PTRLST_HEADER(rule_lst, Rule)
PTRLST_HEADER(pattern_lst, Pattern)
PTRLST_HEADER(pat_elem_lst, PatElem)

#include "dllist.h"
#include "parser.h"

bool str_in_lst(str_lst_t* lst, Str str);
bool is_a_term(Pstate* state, Str str);
bool is_a_nonterm(Pstate* state, Str str);
Str ast_header_name(Str name);
Str ast_source_name(Str name);
Str ast_lock_name(Str name);
Str parser_header_name(Str name);
Str parser_source_name(Str name);
Str parser_lock_name(Str name);
Str scanner_header_name(Str name);
Str scanner_lock_name(Str name);

#endif /* _UTILS_H */
