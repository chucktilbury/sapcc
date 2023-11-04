#ifndef _SCANNER_H
#define _SCANNER_H

#include "logger.h"
#include "util.h"
#include <stddef.h>

typedef enum {
    END_OF_INPUT, // end of input
    ERROR,        // scanner error
    TOKENS,       // The %tokens keyword
    GRAMMAR,      // the %grammar keyword
    SOURCE,       // the %source keyword
    HEADER,       // the %header keyword
    BLOCK,        // a generic '{'.*'}' block
    SYMBOL,       // a generic name: [a-zA-Z][a-zA-Z0-9]*
    NUMBER,       // a generic number: [0-9]*
    COLON,        // a ':' character
    SEMI,         // a ';' character
    OBRACE,       // a '{'
    CBRACE,       // a '}'
} TokenType;

typedef struct {
    Str* str;
    TokenType type;
} Token;

typedef struct {
    Token* token;
    char* buffer;
    size_t size;
    size_t head;
    size_t tail;
    const char* fname;
    size_t line;
    size_t col;
} Scanner;

void init_scanner(const char* fname);
void destroy_scanner();
Token* get_token();
void consume_token();
const char* tok_type_to_str(TokenType type);
int scan_block();
void skip_whitespace();

#endif /* _SCANNER_H */
