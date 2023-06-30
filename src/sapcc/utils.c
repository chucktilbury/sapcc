
#include <string.h>

#include "errors.h"
#include "memory.h"
#include "utils.h"

PTRLST_IMPL(str_lst, STR)
PTRLST_IMPL(rule_lst, Rule)
PTRLST_IMPL(pattern_lst, Pattern)
PTRLST_IMPL(pat_elem_lst, PatElem)

// Returns true if the string is in the str_lst. This has to
// work without disturbing the state of the actual list.
bool str_in_lst(str_lst_t* lst, STR str) {

    for(unsigned int i = 0; i < str_lst_len(lst); i++) {
        if(!strcmp(raw_str(str_lst_get(lst, i)), raw_str(str)))
            return true;
    }

    return false;
}

bool is_a_term(Pstate* state, STR str) {

    return str_in_lst(state->terminals, str);
}

bool is_a_nonterm(Pstate* state, STR str) {

    return str_in_lst(state->non_terminals, str);
}

STR scanner_header_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("scanner.h");
    else
        tmp = create_str_fmt("scanner_%s.h", raw_str(name));

    return tmp;
}

STR scanner_lock_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("_SCANNER_HEADER");
    else {
        tmp = create_str(raw_str(name));
        upcase_str(tmp);
        tmp = create_str_fmt("_SCANNER_%s_HEADER", raw_str(tmp));
    }

    return tmp;
}

STR ast_header_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("ast.h");
    else
        tmp = create_str_fmt("ast_%s.h", raw_str(name));

    return tmp;
}

STR ast_source_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("ast.c");
    else
        tmp = create_str_fmt("ast_%s.c", raw_str(name));

    return tmp;
}

STR ast_lock_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("_AST_HEADER");
    else {
        tmp = create_str(raw_str(name));
        upcase_str(tmp);
        tmp = create_str_fmt("_AST_%s_HEADER", raw_str(tmp));
    }

    return tmp;
}

STR parser_source_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("parser.c");
    else
        tmp = create_str_fmt("parser_%s.c", raw_str(name));

    return tmp;
}

STR parser_header_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("parser.h");
    else
        tmp = create_str_fmt("parser_%s.h", raw_str(name));

    return tmp;
}

STR parser_lock_name(STR name) {

    STR tmp;
    if(len_str(name) == 0)
        tmp = create_str("_PARSER_HEADER");
    else {
        tmp = create_str(raw_str(name));
        upcase_str(tmp);
        tmp = create_str_fmt("_PARSER_%s_HEADER", raw_str(tmp));
    }

    return tmp;
}
