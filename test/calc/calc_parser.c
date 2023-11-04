/* This file is generated by SAPCC. Edits may be lost. */
#include "util.h"

typedef enum {
    _nterm_expression = 1000,
    _nterm_expr_term = 1001,
    _nterm_expr_pow = 1002,
    _nterm_expr_fact = 1003,
    _nterm_expr_unary = 1004,
    _nterm_primary = 1005,
    _nterm_const_expression = 1006,
} NonTerminalType;

#include "calc_parser.h"
#include "calc_scanner.h"

// parser table encoding
static uint16_t parser_table[] = {
    7,

    5,
    _nterm_expression,
    1,
        1, _nterm_expr_term,

    11,
    _nterm_expr_term,
    2,
        3, _nterm_expr_pow, _TOK_ADD, _nterm_expr_term,
        3, _nterm_expr_pow, _TOK_SUB, _nterm_expr_term,

    7,
    _nterm_expr_pow,
    1,
        3, _nterm_expr_fact, _TOK_POW, _nterm_expr_pow,

    15,
    _nterm_expr_fact,
    3,
        3, _nterm_expr_unary, _TOK_MUL, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_DIV, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_MOD, _nterm_expr_fact,

    8,
    _nterm_expr_unary,
    2,
        2, _TOK_SUB, _nterm_expression,
        1, _nterm_primary,

    9,
    _nterm_primary,
    2,
        1, _nterm_const_expression,
        3, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    9,
    _nterm_const_expression,
    3,
        1, _TOK_FLOAT_CONST,
        1, _TOK_INT_CONST,
        1, _TOK_UNSIGNED_CONST
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
    uint16_t num_lines;  // number of rule lines
    RuleLine** list;     // list of lines in the rule
} Rule;

// rule line to use while matching a rule.
typedef struct {
    uint16_t nterm;
    uint16_t score;
    RuleLine * line;
} RuleCacheEntry;

// list of cache entries
typedef List RuleList;

// datastructure to use to match a rule.
typedef struct {
    int index;
    RuleList* list;
} RuleCache;

// list of rule caches
typedef List RuleCacheList;

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
        ptr->list = _ALLOC_ARRAY(RuleLine*, tmp[2]); //malloc(sizeof(uint16_t*)*tmp[2]);
        uint16_t* index = &tmp[3];
        for(uint16_t i = 0; i < tmp[2]; i++) {
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
    printf("lines: %u\n", ptr->num_lines);
    for(unsigned int i = 0; i < ptr->num_lines; i++)
        dump_line(ptr->list[i]);
    printf("\n");
}

int main() {

    Rule* ptr = (Rule*)get_rule(_nterm_expr_term);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(_nterm_primary);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(_nterm_expr_fact);
    dump_rule(ptr);

    ptr = (Rule*)get_rule(8012);
    printf("rule == NULL? %s\n", ptr==NULL? "true":"false");

    return 0;
}
#endif

