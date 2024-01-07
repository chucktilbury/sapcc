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
#include "calc_ast.h"

#define BASE_TERM 500
#define BASE_NTERM 1000

// parser table encoding
static uint16_t parser_table[] = {
    7,

    6,
    _nterm_expression,
    100,
    1,
        1, _nterm_expr_term,

    12,
    _nterm_expr_term,
    1,
    2,
        3, _nterm_expr_pow, _TOK_ADD, _nterm_expr_term,
        3, _nterm_expr_pow, _TOK_SUB, _nterm_expr_term,

    8,
    _nterm_expr_pow,
    3,
    1,
        3, _nterm_expr_fact, _TOK_POW, _nterm_expr_pow,

    16,
    _nterm_expr_fact,
    2,
    3,
        3, _nterm_expr_unary, _TOK_MUL, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_DIV, _nterm_expr_fact,
        3, _nterm_expr_unary, _TOK_MOD, _nterm_expr_fact,

    9,
    _nterm_expr_unary,
    4,
    2,
        2, _TOK_SUB, _nterm_expression,
        1, _nterm_primary,

    10,
    _nterm_primary,
    100,
    2,
        1, _nterm_const_expression,
        3, _TOK_OPAREN, _nterm_expression, _TOK_CPAREN,

    6,
    _nterm_const_expression,
    100,
    1,
        1, _TOK_INT_CONST
};


typedef struct {
    uint16_t len;   // length of this line
    uint16_t* line; // list of items in the line
    int score;      // score of this cache line
    int index;      // index of the last match
} CacheLine;

typedef struct {
    int size;           // lines in the cache
    CacheLine** lines;  // the actual lines
} Cache;

typedef struct _rule_ {
    uint16_t size;       // the non-terminal value
    uint16_t type;       // the non-terminal value
    uint16_t prec;       // rule precedence
    uint16_t num_lines;  // number of rule lines
    CacheLine** list;     // list of lines in the rule
} Rule;

static const char* nterm_to_str(uint16_t type) {
    return (type == _nterm_expression)? "expression" :
        (type == _nterm_expr_term)? "expr_term" :
        (type == _nterm_expr_pow)? "expr_pow" :
        (type == _nterm_expr_fact)? "expr_fact" :
        (type == _nterm_expr_unary)? "expr_unary" :
        (type == _nterm_primary)? "primary" :
        (type == _nterm_const_expression)? "const_expression" :
                "UNKNOWN";
}

static int errors = 0;
static int warnings = 0;
#include <stdarg.h>

static void syntax_error(const char* fmt, ...) {

    va_list args;

    if(get_line_no() > 0)
        fprintf(stderr, "Syntax Error: %s:%d:%d ", get_fname(), get_line_no(), get_col_no());
    else
        fprintf(stderr, "Syntax Error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");

    errors++;
}

static void syntax_error_token(Token* tok, const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "Syntax Error: %s:%d:%d ", raw_string(tok->fname), tok->line_no, tok->col_no);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");

    errors++;
}

static void syntax_warning(const char* fmt, ...) {

    va_list args;

    if(get_line_no() > 0)
        fprintf(stderr, "Warning: %s:%d:%d ", get_fname(), get_line_no(), get_col_no());
    else
        fprintf(stderr, "Warning: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");

    warnings++;
}

static void fatal_error(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "Fatal Error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");

    errors++;
    exit(1);
}

int get_errors() {
    return errors;
}

int get_wanings() {
    return warnings;
}



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

static CacheLine* get_line(uint16_t* table) {

    CacheLine* ptr = _ALLOC_T(CacheLine);
    ptr->len = table[0];
    ptr->line = _ALLOC_ARRAY(uint16_t, table[0]);
    memcpy(ptr->line, &table[1], sizeof(uint16_t)*table[0]+1);

    return ptr;
}

static Rule* get_rule(uint16_t type) {

    uint16_t* tmp = find_rule(type);
    Rule* ptr;

    if(tmp == NULL)
        return NULL;
    else {
        ptr = _DUP_MEM_ARRAY(tmp, Rule, tmp[0]);
        ptr->list = _ALLOC_ARRAY(CacheLine*, tmp[3]);
        uint16_t* index = &tmp[4];
        for(uint16_t i = 0; i < tmp[3]; i++) {
            ptr->list[i] = get_line(index);
            index += index[0]+1;
        }
    }

    return ptr;
}

static inline bool is_term(uint16_t type) {
    return (type >= BASE_TERM && type < BASE_NTERM)? true: false;
}

static inline bool is_nterm(uint16_t type) {
    return (type < BASE_NTERM)? false: true;
}

static Cache* create_cache(uint16_t type) {

    const uint16_t* rule = find_rule(type);
    if(!rule)
        fatal_error("match_rule: unknown rule: %u\n", type);

    Cache* cache = _ALLOC_T(Cache);
    cache->size = rule[3];
    cache->lines = _ALLOC_ARRAY(CacheLine*, cache->size);

    uint16_t* tpt = &rule[4];
    for(uint16_t i = 0; i < rule[3]; i++) {
        CacheLine* line = _ALLOC_T(CacheLine);
        line->score = 0;
        line->index = 0;
        line->len = tpt[0];
        line->line = _ALLOC_ARRAY(uint16_t, line->len);
        for(uint16_t j = 0; j < line->len; j++)
            line->line[j] = tpt[j+1];
        cache->lines[i] = line;
        tpt += tpt[0]+1;
    }

    return cache;
}

static Ast* match_rule_line(CacheLine* line, bool final) {

}

static Ast* match_rule(uint16_t type, bool final) {

    // create the cache
    Cache* cache = create_cache(type);
    List* out = create_list(sizeof(AstEntry*));

    // evaluate the rule
    int index = 0;
    int line = 0;
    int count = cache->size;
    CacheLine** lines = (CacheLine**)raw_list(cache->lines);
    while(true) {
        line = 0;
        Token* tok = get_token();
        for(CacheLine* line = lines[line]; line < cache->size; line++) {
            if((index < line->size) && (line->score >= 0)) {
                if(is_nterm(line->line[index])) {

                }
                else {
                    // recurse the non-terminal
                    Ast* ast = match_rule(line->line[index], (count > 1)? false: true);
                    if(ast) {
                        // obtained a match on this rule index

                    }
                    else {
                        // no match so negate this rule.
                        // (errors can only happen on a term)
                        line->score = -1;
                    }
                }
            }
        }
    }

    // pass/fail
    return create_ast_node(type, out);
}

Ast* parse() {

    return match_rule(BASE_NTERM, true);
}

#if 1
static void dump_line_obj(uint16_t obj) {    if(is_nterm(obj))
        printf("%s", nterm_to_str(obj));
    else
        printf("%u", obj);
}

static void dump_line(CacheLine* line) {

    printf("    len:%d ", line->len);
    printf("score:%d ", line->score);
    printf("index:%d [", line->index);
    int idx = 0;
    dump_line_obj(line->line[idx++]);
    while(idx < line->len) {
        printf(", ");
        dump_line_obj(line->line[idx++]);
    }
    printf("]\n");
}

static void dump_cache(Cache* ptr) {

    printf("line: ");
    printf("size:%u\n", ptr->size);
    for(int i = 0; i < ptr->size; i++)
        dump_line(ptr->lines[i]);
    printf("\n");
}

static void dump_rule(Rule* ptr) {

    printf("size:%u\n", ptr->size);
    printf("type:"); dump_line_obj(ptr->type); printf("\n");
    printf("prec:%u\n", ptr->prec);
    printf("lines:%u\n", ptr->num_lines);
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

    Cache* c = create_cache(1005);
    dump_cache(c);

    return 0;
}
#endif
