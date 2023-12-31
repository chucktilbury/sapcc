/* This file is generated by SAPCC. Edits may be lost. */
#include "util.h"

typedef enum {
    _nterm_module = 1000,
    _nterm_module_element = 1001,
    _nterm_module_body = 1002,
    _nterm_entry_definition = 1003,
    _nterm_scope = 1004,
    _nterm_type_name = 1005,
    _nterm_compound_name = 1006,
    _nterm_compound_reference = 1007,
    _nterm_compound_reference_element = 1008,
    _nterm_formatted_string = 1009,
    _nterm_func_reference = 1010,
    _nterm_array_reference = 1011,
    _nterm_array_reference_list = 1012,
    _nterm_import_statement = 1013,
    _nterm_namespace_definition = 1014,
    _nterm_namespace_block = 1015,
    _nterm_namespace_element = 1016,
    _nterm_class_definition = 1017,
    _nterm_class_parameters = 1018,
    _nterm_class_block = 1019,
    _nterm_class_body = 1020,
    _nterm_class_body_element = 1021,
    _nterm_var_declaration = 1022,
    _nterm_func_declaration = 1023,
    _nterm_func_decl_parms = 1024,
    _nterm_func_decl_parms_list = 1025,
    _nterm_func_decl_parms_elem = 1026,
    _nterm_bool_literal = 1027,
    _nterm_primary = 1028,
    _nterm_const_expression = 1029,
    _nterm_expression = 1030,
    _nterm_expr_or = 1031,
    _nterm_expr_and = 1032,
    _nterm_expr_equ = 1033,
    _nterm_expr_comp = 1034,
    _nterm_expr_term = 1035,
    _nterm_expr_pow = 1036,
    _nterm_expr_fact = 1037,
    _nterm_expr_unary = 1038,
    _nterm_cast_expr = 1039,
    _nterm_expr_list = 1040,
    _nterm_member = 1041,
    _nterm_func_definition = 1042,
    _nterm_ctor_definition = 1043,
    _nterm_dtor_definition = 1044,
    _nterm_func_block = 1045,
    _nterm_assignment_oper = 1046,
    _nterm_assignment = 1047,
    _nterm_data_definition = 1048,
    _nterm_func_content = 1049,
    _nterm_func_content_elem = 1050,
    _nterm_inline_block = 1051,
    _nterm_print_statement = 1052,
    _nterm_break_statement = 1053,
    _nterm_cont_statement = 1054,
    _nterm_trace_statement = 1055,
    _nterm_yield_statement = 1056,
    _nterm_exit_statement = 1057,
    _nterm_return_statement = 1058,
    _nterm_raise_statement = 1059,
    _nterm_if_else_clause = 1060,
    _nterm_if_clause = 1061,
    _nterm_else_clause = 1062,
    _nterm_else_clause_list = 1063,
    _nterm_else_clause_final = 1064,
    _nterm_while_clause = 1065,
    _nterm_do_clause = 1066,
    _nterm_for_clause = 1067,
    _nterm_switch_case_clause = 1068,
    _nterm_switch_clause = 1069,
    _nterm_case_clause = 1070,
    _nterm_case_clause_list = 1071,
    _nterm_case_clause_final = 1072,
    _nterm_try_except_clause = 1073,
    _nterm_try_clause = 1074,
    _nterm_except_clause = 1075,
    _nterm_except_clause_list = 1076,
    _nterm_except_clause_final = 1077,
} NonTerminalType;

#include "simple_parser.h"
#include "simple_scanner.h"

// parser table encoding
static uint16_t parser_table[] = {
    78,

    6,
    _nterm_module,
    100,
    1,
        1, _nterm_module_body,

    10,
    _nterm_module_element,
    100,
    3,
        1, _nterm_namespace_element,
        1, _nterm_import_statement,
        1, _nterm_entry_definition,

    9,
    _nterm_module_body,
    100,
    2,
        1, _nterm_module_element,
        2, _nterm_module_body, _nterm_module_element,

    7,
    _nterm_entry_definition,
    100,
    1,
        2, _TOK_ENTRY, _nterm_func_block,

    10,
    _nterm_scope,
    100,
    3,
        1, _TOK_PUBLIC,
        1, _TOK_PRIVATE,
        1, _TOK_PROTECTED,

    22,
    _nterm_type_name,
    100,
    9,
        1, _nterm_compound_name,
        1, _TOK_FLOAT,
        1, _TOK_INTEGER,
        1, _TOK_UNSIGNED,
        1, _TOK_STRING,
        1, _TOK_DICT,
        1, _TOK_LIST,
        1, _TOK_BOOLEAN,
        1, _TOK_NOTHING,

    10,
    _nterm_compound_name,
    100,
    2,
        1, _TOK_SYMBOL,
        3, _nterm_compound_name, _TOK_DOT, _TOK_SYMBOL,

    10,
    _nterm_compound_reference,
    100,
    2,
        1, _nterm_compound_reference_element,
        3, _nterm_compound_reference, _TOK_DOT, _nterm_compound_reference_element,

    10,
    _nterm_compound_reference_element,
    100,
    3,
        1, _TOK_SYMBOL,
        1, _nterm_func_reference,
        1, _nterm_array_reference,

    15,
    _nterm_formatted_string,
    100,
    3,
        1, _TOK_STRG_CONST,
        3, _TOK_STRG_CONST, _TOK_OPAREN, _TOK_CPAREN,
        4, _TOK_STRG_CONST, _TOK_OPAREN, _nterm_expr_list, _TOK_CPAREN,

    13,
    _nterm_func_reference,
    100,
    2,
        3, _nterm_compound_name, _TOK_OPAREN, _TOK_CPAREN,
        4, _nterm_compound_name, _TOK_OPAREN, _nterm_expr_list, _TOK_CPAREN,

    7,
    _nterm_array_reference,
    100,
    1,
        2, _nterm_compound_name, _nterm_array_reference_list,

    13,
    _nterm_array_reference_list,
    100,
    2,
        3, _TOK_OBRACE, _nterm_expression, _TOK_CBRACE,
        4, _nterm_array_reference_list, _TOK_OBRACE, _nterm_expression, _TOK_CBRACE,

    12,
    _nterm_import_statement,
    100,
    2,
        2, _TOK_IMPORT, _nterm_compound_name,
        4, _TOK_IMPORT, _nterm_compound_name, _TOK_AS, _TOK_SYMBOL,

    10,
    _nterm_namespace_definition,
    100,
    1,
        5, _TOK_NAMESPACE, _TOK_SYMBOL, _TOK_OBLOCK, _nterm_namespace_block, _TOK_CBLOCK,

    9,
    _nterm_namespace_block,
    100,
    2,
        1, _nterm_namespace_element,
        2, _nterm_namespace_block, _nterm_namespace_element,

    18,
    _nterm_namespace_element,
    100,
    7,
        1, _nterm_namespace_definition,
        1, _nterm_class_definition,
        1, _nterm_func_definition,
        1, _nterm_ctor_definition,
        1, _nterm_dtor_definition,
        1, _nterm_var_declaration,
        1, _nterm_scope,

    9,
    _nterm_class_definition,
    100,
    1,
        4, _TOK_CLASS, _TOK_SYMBOL, _nterm_class_parameters, _nterm_class_block,

    11,
    _nterm_class_parameters,
    100,
    2,
        2, _TOK_OPAREN, _TOK_CPAREN,
        3, _TOK_OPAREN, _nterm_compound_name, _TOK_CPAREN,

    11,
    _nterm_class_block,
    100,
    2,
        2, _TOK_OBLOCK, _TOK_CBLOCK,
        3, _TOK_OBLOCK, _nterm_class_body, _TOK_CBLOCK,

    9,
    _nterm_class_body,
    100,
    2,
        1, _nterm_class_body_element,
        2, _nterm_class_body, _nterm_class_body_element,

    10,
    _nterm_class_body_element,
    100,
    3,
        1, _nterm_var_declaration,
        1, _nterm_func_declaration,
        1, _nterm_scope,

    7,
    _nterm_var_declaration,
    100,
    1,
        2, _nterm_type_name, _TOK_SYMBOL,

    13,
    _nterm_func_declaration,
    100,
    3,
        3, _nterm_type_name, _TOK_SYMBOL, _nterm_func_decl_parms,
        2, _TOK_CREATE, _nterm_func_decl_parms,
        1, _TOK_DESTROY,

    11,
    _nterm_func_decl_parms,
    100,
    2,
        2, _TOK_OPAREN, _TOK_CPAREN,
        3, _TOK_OPAREN, _nterm_func_decl_parms_list, _TOK_CPAREN,

    10,
    _nterm_func_decl_parms_list,
    100,
    2,
        1, _nterm_func_decl_parms_elem,
        3, _nterm_func_decl_parms_list, _TOK_COMMA, _nterm_func_decl_parms_elem,

    7,
    _nterm_func_decl_parms_elem,
    100,
    1,
        2, _nterm_type_name, _TOK_SYMBOL,

    8,
    _nterm_bool_literal,
    100,
    2,
        1, _TOK_TRUE,
        1, _TOK_FALSE,

    14,
    _nterm_primary,
    100,
    4,
        1, _nterm_compound_reference,
        1, _nterm_const_expression,
        1, _nterm_cast_expr,
        3, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    14,
    _nterm_const_expression,
    100,
    5,
        1, _nterm_formatted_string,
        1, _nterm_bool_literal,
        1, _TOK_FLOAT_CONST,
        1, _TOK_INT_CONST,
        1, _TOK_UNSIGNED_CONST,

    6,
    _nterm_expression,
    100,
    1,
        1, _nterm_expr_or,

    8,
    _nterm_expr_or,
    100,
    1,
        3, _nterm_expr_and, _TOK_OR, _nterm_expr_or,

    8,
    _nterm_expr_and,
    100,
    1,
        3, _nterm_expr_equ, _TOK_AND, _nterm_expr_and,

    12,
    _nterm_expr_equ,
    100,
    2,
        3, _nterm_expr_comp, _TOK_EQU, _nterm_expr_equ,
        3, _nterm_expr_comp, _TOK_NEQU, _nterm_expr_equ,

    20,
    _nterm_expr_comp,
    100,
    4,
        3, _nterm_expr_term, _TOK_LORE, _nterm_expr_comp,
        3, _nterm_expr_term, _TOK_GORE, _nterm_expr_comp,
        3, _nterm_expr_term, _TOK_CPOINT, _nterm_expr_comp,
        3, _nterm_expr_term, _TOK_OPOINT, _nterm_expr_comp,

    12,
    _nterm_expr_term,
    100,
    2,
        3, _nterm_expr_pow, _TOK_ADD, _nterm_expr_term,
        3, _nterm_expr_pow, _TOK_SUB, _nterm_expr_term,

    8,
    _nterm_expr_pow,
    100,
    1,
        3, _nterm_expr_fact, _TOK_POW, _nterm_expr_pow,

    16,
    _nterm_expr_fact,
    100,
    3,
        3, _nterm_expr_unary, _TOK_MUL, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_DIV, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_MOD, _nterm_expr_fact,

    12,
    _nterm_expr_unary,
    100,
    3,
        2, _TOK_NOT, _nterm_expression,
        2, _TOK_SUB, _nterm_expression,
        1, _nterm_primary,

    9,
    _nterm_cast_expr,
    100,
    1,
        4, _TOK_OPOINT, _nterm_type_name, _TOK_CPOINT, _nterm_expression,

    10,
    _nterm_expr_list,
    100,
    2,
        1, _nterm_expression,
        3, _nterm_expr_list, _TOK_COMMA, _nterm_expression,

    7,
    _nterm_member,
    100,
    1,
        2, _TOK_SYMBOL, _TOK_COLON,

    10,
    _nterm_func_definition,
    100,
    1,
        5, _nterm_type_name, _nterm_member, _TOK_SYMBOL, _nterm_func_decl_parms, _nterm_func_block,

    9,
    _nterm_ctor_definition,
    100,
    1,
        4, _nterm_member, _TOK_CREATE, _nterm_func_decl_parms, _nterm_func_block,

    8,
    _nterm_dtor_definition,
    100,
    1,
        3, _nterm_member, _TOK_DESTROY, _nterm_func_block,

    11,
    _nterm_func_block,
    100,
    2,
        2, _TOK_OBLOCK, _TOK_CBLOCK,
        3, _TOK_OBLOCK, _nterm_func_content, _TOK_CBLOCK,

    16,
    _nterm_assignment_oper,
    100,
    6,
        1, _TOK_ASSIGN,
        1, _TOK_ADD_ASSIGN,
        1, _TOK_SUB_ASSIGN,
        1, _TOK_MUL_ASSIGN,
        1, _TOK_DIV_ASSIGN,
        1, _TOK_MOD_ASSIGN,

    7,
    _nterm_assignment,
    100,
    1,
        2, _nterm_assignment_oper, _nterm_expression,

    9,
    _nterm_data_definition,
    100,
    2,
        1, _nterm_var_declaration,
        2, _nterm_var_declaration, _nterm_assignment,

    9,
    _nterm_func_content,
    100,
    2,
        1, _nterm_func_content_elem,
        2, _nterm_func_content, _nterm_func_content_elem,

    43,
    _nterm_func_content_elem,
    100,
    19,
        1, _nterm_func_block,
        1, _nterm_data_definition,
        1, _nterm_compound_reference,
        2, _nterm_compound_reference, _nterm_assignment,
        1, _nterm_if_else_clause,
        1, _nterm_while_clause,
        1, _nterm_do_clause,
        1, _nterm_for_clause,
        1, _nterm_switch_case_clause,
        1, _nterm_try_except_clause,
        1, _nterm_return_statement,
        1, _nterm_raise_statement,
        1, _nterm_exit_statement,
        1, _nterm_yield_statement,
        1, _nterm_trace_statement,
        1, _nterm_print_statement,
        1, _nterm_break_statement,
        1, _nterm_cont_statement,
        1, _nterm_inline_block,

    7,
    _nterm_inline_block,
    100,
    1,
        2, _TOK_INLINE, _nterm_formatted_string,

    15,
    _nterm_print_statement,
    100,
    3,
        1, _TOK_PRINT,
        3, _TOK_PRINT, _TOK_OPAREN, _TOK_CPAREN,
        4, _TOK_PRINT, _TOK_OPAREN, _nterm_formatted_string, _TOK_CPAREN,

    6,
    _nterm_break_statement,
    100,
    1,
        1, _TOK_BREAK,

    6,
    _nterm_cont_statement,
    100,
    1,
        1, _TOK_CONTINUE,

    15,
    _nterm_trace_statement,
    100,
    3,
        1, _TOK_TRACE,
        3, _TOK_TRACE, _TOK_OPAREN, _TOK_CPAREN,
        4, _TOK_TRACE, _TOK_OPAREN, _nterm_formatted_string, _TOK_CPAREN,

    9,
    _nterm_yield_statement,
    100,
    1,
        4, _TOK_YIELD, _TOK_OPAREN, _TOK_SYMBOL, _TOK_CPAREN,

    9,
    _nterm_exit_statement,
    100,
    1,
        4, _TOK_EXIT, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    15,
    _nterm_return_statement,
    100,
    3,
        1, _TOK_RETURN,
        3, _TOK_RETURN, _TOK_OPAREN, _TOK_CPAREN,
        4, _TOK_RETURN, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    9,
    _nterm_raise_statement,
    100,
    1,
        4, _TOK_RAISE, _TOK_OPAREN, _nterm_compound_name, _TOK_CPAREN,

    13,
    _nterm_if_else_clause,
    100,
    3,
        1, _nterm_if_clause,
        2, _nterm_if_clause, _nterm_else_clause_list,
        3, _nterm_if_clause, _nterm_else_clause_list, _nterm_else_clause_final,

    10,
    _nterm_if_clause,
    100,
    1,
        5, _TOK_IF, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN, _nterm_func_block,

    10,
    _nterm_else_clause,
    100,
    1,
        5, _TOK_ELSE, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN, _nterm_func_block,

    9,
    _nterm_else_clause_list,
    100,
    2,
        1, _nterm_else_clause,
        2, _nterm_else_clause_list, _nterm_else_clause,

    12,
    _nterm_else_clause_final,
    100,
    2,
        4, _TOK_ELSE, _TOK_OPAREN, _TOK_CPAREN, _nterm_func_block,
        2, _TOK_ELSE, _nterm_func_block,

    10,
    _nterm_while_clause,
    100,
    1,
        5, _TOK_WHILE, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN, _nterm_func_block,

    11,
    _nterm_do_clause,
    100,
    1,
        6, _TOK_DO, _nterm_func_block, _TOK_WHILE, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    22,
    _nterm_for_clause,
    100,
    2,
        7, _TOK_FOR, _TOK_OPAREN, _TOK_SYMBOL, _TOK_IN, _nterm_compound_reference, _TOK_CPAREN, _nterm_func_block,
        9, _TOK_FOR, _TOK_OPAREN, _TOK_SYMBOL, _TOK_IN, _nterm_expression, _TOK_TO, _nterm_expression, _TOK_CPAREN, _nterm_func_block,

    8,
    _nterm_switch_case_clause,
    100,
    1,
        3, _nterm_switch_clause, _nterm_case_clause_list, _nterm_case_clause_final,

    10,
    _nterm_switch_clause,
    100,
    1,
        5, _TOK_SWITCH, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN, _TOK_OBLOCK,

    10,
    _nterm_case_clause,
    100,
    1,
        5, _TOK_CASE, _TOK_OPAREN, _nterm_const_expression, _TOK_CPAREN, _nterm_func_block,

    9,
    _nterm_case_clause_list,
    100,
    2,
        1, _nterm_case_clause,
        2, _nterm_case_clause_list, _nterm_case_clause,

    10,
    _nterm_case_clause_final,
    100,
    2,
        1, _TOK_CBLOCK,
        3, _TOK_DEFAULT, _nterm_func_block, _TOK_CBLOCK,

    8,
    _nterm_try_except_clause,
    100,
    1,
        3, _nterm_try_clause, _nterm_except_clause_list, _nterm_except_clause_final,

    7,
    _nterm_try_clause,
    100,
    1,
        2, _TOK_TRY, _nterm_func_block,

    10,
    _nterm_except_clause,
    100,
    1,
        5, _TOK_EXCEPT, _TOK_OPAREN, _nterm_compound_name, _TOK_CPAREN, _nterm_func_block,

    9,
    _nterm_except_clause_list,
    100,
    2,
        1, _nterm_except_clause,
        2, _nterm_except_clause_list, _nterm_except_clause,

    12,
    _nterm_except_clause_final,
    100,
    2,
        4, _TOK_EXCEPT, _TOK_OPAREN, _TOK_CPAREN, _nterm_func_block,
        2, _TOK_EXCEPT, _nterm_func_block
};

#include <stdint.h>
#include "util.h"

typedef struct {
    uint16_t len;    // length of this line
    uint16_t* line;  // list of items in the line
} RuleLine;

typedef struct _rule_ {
    uint16_t size;       // the non-terminal value
    uint16_t type;       // the non-terminal value
    uint16_t prec;       // rule precedence
    uint16_t num_lines;  // number of rule lines
    RuleLine** list;     // list of lines in the rule
} Rule;

static uint16_t* find_rule(uint16_t type) {

    uint16_t* tmp;
    int idx = 1;

    for(uint16_t i = 0; i < parser_table[0]; i++) {
        tmp = &parser_table[idx];
        if(tmp[1] == type)
            return tmp;
        else
            idx += tmp[0];
    }

    return NULL;
}

static RuleLine* get_line(uint16_t* table) {

    RuleLine* ptr = _ALLOC_T(RuleLine);
    ptr->len = table[0];
    ptr->line = _ALLOC_ARRAY(uint16_t, table[0]);
    memcpy(ptr->line, &table[1], sizeof(unsigned int)*table[0]+1);

    return ptr;
}

static Rule* get_rule(uint16_t type) {

    uint16_t* tmp = find_rule(type);
    Rule* ptr;

    if(tmp == NULL)
        return NULL;
    else {
        ptr = _DUP_MEM_ARRAY(tmp, Rule, tmp[0]);
        ptr->list = _ALLOC_ARRAY(RuleLine*, tmp[3]);
        uint16_t* index = &tmp[4];
        for(uint16_t i = 0; i < tmp[3]; i++) {
            ptr->list[i] = get_line(index);
            index += index[0]+1;
        }
    }

    return ptr;
}

#if 1
// build string:
// gcc -Wall -Wextra -Wpedantic -o t simple_parser.c -I../src/util -L../bin -lutil -lgc
static void dump_line(RuleLine* line) {

    printf("    len: %d\n", line->len);
    int idx = 0;
    printf("    %u", line->line[idx++]);
    while(idx < line->len) {
        printf(", ");
        printf("%u", line->line[idx++]);
    }
    printf("\n");
}

static void dump_rule(Rule* ptr) {

    printf("size: %u\n", ptr->size);
    printf("type: %u\n", ptr->type);
    printf("prec: %u\n", ptr->prec);
    printf("lines: %u\n", ptr->num_lines);
    for(unsigned int i = 0; i < ptr->num_lines; i++)
        dump_line(ptr->list[i]);
    printf("\n");
}

int main() {

    Rule* ptr = (Rule*)get_rule(1001);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(1003);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(1006);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(8012);
    printf("rule == NULL? %s\n", ptr==NULL? "true":"false");

    return 0;
}
#endif

