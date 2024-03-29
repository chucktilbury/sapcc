/* This file is generated by SAPCC. Edits may be lost. */
#ifndef _CALC_SCANNER_H
#define _CALC_SCANNER_H

typedef enum {
    _TOK_OPAREN = 500,
    _TOK_CPAREN = 501,
    _TOK_ADD = 502,
    _TOK_SUB = 503,
    _TOK_POW = 504,
    _TOK_MUL = 505,
    _TOK_DIV = 506,
    _TOK_MOD = 507,
    _TOK_INT_CONST = 508,
} TokenType;

typedef struct {
    Str* str;
    TokenType type;
    int line_no;
    int col_no;
    Str* fname;
} Token;

extern Token token;

/*
    Public Interface.
 */
Token* create_token();
void open_file(const char* fname);
Token* get_token();
void unconsume_token(Token* tok);
void consume_token();
int get_line_no();
int get_col_no();
const char* get_fname();
const char* tok_to_str(TokenType type);


#endif

