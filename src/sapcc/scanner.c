
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "errors.h"
#include "fileio.h"
#include "memory.h"
#include "scanner.h"

#define IS_SYMBOL(c) (isalpha(c) || (c) == '_')
#define IS_SYMBOL1(c) (isalnum(c) || (c) == '_')
#if 0
#define TEST_EOF(f, ...)                 \
    do {                                 \
        if(get_char() > 0x7F)            \
            syntax((f), ##__VA_ARGS__);  \
        fatal("unexpected end of file"); \
    } while(false)
#endif

static Token _tok;

static void check_eof(const char* fmt, ...) {

    va_list args;

    if(get_char() > 0x7F) {
        va_start(args, fmt);
        syntax(fmt, args);
        va_end(args);
        fatal("unexpected end of file");
    }
}

static void consume_space() {

    int ch = get_char();
    while(isspace(ch))
        ch = consume_char();
}

static void consume_comment() {

    int ch = consume_char();
    while(ch != '\n')
        ch = consume_char();
}

static void get_directive() {

    // save the leading '%'
    cat_str_char(_tok.str, get_char());
    consume_char();

    // read normal characters
    int ch = get_char();
    while(IS_SYMBOL(ch)) {
        cat_str_char(_tok.str, ch);
        ch = consume_char();
        // TEST_EOF("invalid directive: %s", raw_str(_tok.str));
        check_eof("invalid directive: %s", raw_str(_tok.str));
    }

    if(!strcmp(raw_str(_tok.str), "%verbosity"))
        _tok.type = VERBOSITY;
    else if(!strcmp(raw_str(_tok.str), "%name"))
        _tok.type = NAME;
    else if(!strcmp(raw_str(_tok.str), "%prefix"))
        _tok.type = PREFIX;
    else if(!strcmp(raw_str(_tok.str), "%code"))
        _tok.type = CODE;
    else {
        _tok.type = ERROR;
        syntax("unknown directive: %s", raw_str(_tok.str));
    }
}

static void get_string() {

    consume_char(); // consume the leading '\"'

    int ch = get_char();
    while(ch != '\"') {
        cat_str_char(_tok.str, ch);
        ch = consume_char();
        // TEST_EOF("invalid string");
        check_eof("invalid string");
    }

    consume_char(); // consume the trailing '\"'
    _tok.type = STRG;
}

static void get_number() {

    int ch = get_char();
    cat_str_char(_tok.str, ch);

    while(isdigit(ch = consume_char()))
        cat_str_char(_tok.str, ch);

    _tok.type = NUMBER;
}

static void get_block() {

    // do not save the enclosing {}
    consume_char(); // consume the '{'

    int count = 1;
    while(count > 0) {
        int ch = get_char();
        if(ch == '{') {
            count++;
            cat_str_char(_tok.str, ch);
        }
        else if(ch == '}') {
            count--;
            if(count > 0)
                cat_str_char(_tok.str, ch);
        }
        else
            cat_str_char(_tok.str, ch);

        ch = consume_char();
    }

    _tok.type = BLOCK;
}

static void get_symbol() {

    int ch = get_char();
    if(IS_SYMBOL(ch)) {
        cat_str_char(_tok.str, ch);
        ch = consume_char();
        while(IS_SYMBOL1(ch)) {
            cat_str_char(_tok.str, ch);
            ch = consume_char();
        }
    }
    else {
        _tok.type = ERROR;
        syntax("invalid symbol");
        return;
    }

    _tok.type = SYMBOL;
}


TokenType get_token(Token* tok) {

    if(tok != NULL) {
        tok->type = _tok.type;
        tok->str  = copy_str(_tok.str);
    }
    return _tok.type;
}

TokenType consume_token(Token* tok) {

    bool finished = false;

    if(_tok.str != NULL)
        clear_str(_tok.str);
    else
        _tok.str = create_str(NULL);

    while(!finished) {
        consume_space();
        switch((unsigned char)get_char()) {
            case 0xFF:
                _tok.type = END_OF_INPUT;
                finished  = true;
                break;
            case '#':
                consume_comment();
                break;
            case ':':
                _tok.type = COLON;
                consume_char();
                finished = true;
                break;
            case '%':
                get_directive();
                finished = true;
                break;
            case '\"':
                get_string();
                finished = true;
                break;
            case '{':
                get_block();
                finished = true;
                break;
            default:
                if(isdigit(get_char()))
                    get_number();
                else
                    get_symbol();
                finished = true;
                break;
        }
    }

    if(tok != NULL) {
        tok->str  = copy_str(_tok.str);
        tok->type = _tok.type;
        tok->line = get_line_no();
        tok->col  = get_col_no();
    }

    return _tok.type;
}

const char* tok_to_str(TokenType type) {

    return (type == ERROR) ? "error token" :
    (type == BLOCK)        ? "block definition" :
    (type == COLON)        ? ":" :
    (type == SYMBOL)       ? "symbol definition" :
    (type == STRG)         ? "quoted string" :
    (type == NUMBER)       ? "number" :
    (type == VERBOSITY)    ? "verbosity directive" :
    (type == NAME)         ? "file name directive" :
    (type == PREFIX)       ? "data structure prefix directive" :
    (type == CODE)         ? "code directive" :
                             "UNKNOWN";
}