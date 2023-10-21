
#include "scanner.h"
#include "errors.h"
#include "logger.h"
#include "util.h"
#include <stdarg.h>

#define SLEVEL 20
static int errors   = 0;
static int warnings = 0;

static Scanner* scanner_state;

static void scanner_error(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "Scanner Error: %s: %lu: %lu: ", scanner_state->fname, scanner_state->line, scanner_state->col);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    errors++;
    fputc('\n', stderr);
}

static void scanner_warning(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "Scanner Warning: %s: %lu: %lu: ", scanner_state->fname, scanner_state->line, scanner_state->col);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    warnings++;
    fputc('\n', stderr);
}

static int get_scanner_char() {

    return get_char();
}

static int consume_scanner_char() {

    return consume_char();
}

static Token* create_token() {

    Token* tok = _ALLOC_T(Token);
    tok->str   = create_string(NULL);

    return tok;
}

static void reset_token(Token* tok) {

    clear_string(tok->str);
}

static void destroy_token(Token* tok) {

    if(tok != NULL) {
        destroy_string(tok->str);
        _FREE(tok);
    }
}

static void eat_comment() {

    // consume the '#'
    consume_scanner_char();
    while(get_scanner_char() != '\n')
        consume_scanner_char();
}

static void get_word() {

    int ch = get_scanner_char();

    while(!isspace(ch) && ch != EOF) {
        add_string_char(scanner_state->token->str, ch);
        consume_scanner_char();
        ch = get_scanner_char();
    }
}

static void get_keyword() {

    get_word();

    if(!comp_string_const(scanner_state->token->str, "%tokens"))
        scanner_state->token->type = TOKENS;
    else if(!comp_string_const(scanner_state->token->str, "%grammar"))
        scanner_state->token->type = GRAMMAR;
    else if(!comp_string_const(scanner_state->token->str, "%source"))
        scanner_state->token->type = SOURCE;
    else if(!comp_string_const(scanner_state->token->str, "%header"))
        scanner_state->token->type = HEADER;
    else {
        scanner_error("unknown directive: %s", raw_string(scanner_state->token->str));
        scanner_state->token->type = ERROR;
    }
}

static void get_symbol() {

    get_word();
    scanner_state->token->type = SYMBOL;
}

/*
    Public interface.
 */
void init_scanner(const char* fname) {

    scanner_state = _ALLOC_T(Scanner);

    open_input_file(fname);

    // scanner_state->logger = init_logger(stderr, 5, "Scanner");
    scanner_state->head  = 0;
    scanner_state->tail  = 1;
    scanner_state->line  = 1;
    scanner_state->col   = 1;
    scanner_state->fname = _DUP_STR(fname);

    scanner_state->token = create_token();
    consume_token();
}

void destroy_scanner() {

    if(scanner_state != NULL) {
        if(scanner_state->buffer != NULL)
            _FREE(scanner_state->buffer);
        if(scanner_state->fname != NULL)
            _FREE(scanner_state->fname);
        destroy_token(scanner_state->token);
        _FREE(scanner_state);
    }
}

Token* get_token() {

    return scanner_state->token;
}

void consume_token() {

    int finished = 0;

    while(!finished) {
        reset_token(scanner_state->token);
        int ch = get_scanner_char();
        switch(ch) {
            case EOF:
                scanner_state->token->type = END_OF_INPUT;
                finished++;
                break;
            case '%':
                get_keyword();
                finished++;
                break;
            case '{':
                scanner_state->token->type = OBRACE;
                consume_scanner_char();
                finished++;
                break;
            case '}':
                scanner_state->token->type = CBRACE;
                consume_scanner_char();
                finished++;
                break;
            case ':':
                scanner_state->token->type = COLON;
                consume_scanner_char();
                finished++;
                break;
            case ';':
                scanner_state->token->type = SEMI;
                consume_scanner_char();
                finished++;
                break;
            case '#':
                eat_comment();
                break;
            default:
                if(isspace(ch))
                    consume_scanner_char();
                else if(isalnum(ch)) {
                    get_symbol();
                    finished++;
                }
                else {
                    scanner_warning("unknown character: '%c' (0x%04X)", ch, ch);
                    consume_scanner_char();
                }

                break;
        }
    }
    LOG(SLEVEL, "scanner: %d: %d: \"%s\" (%s)", get_line_no(), get_col_no(), raw_string(scanner_state->token->str),
        tok_type_to_str(scanner_state->token->type));
}

void skip_whitespace() {

    while(isspace(get_scanner_char())) {
        consume_scanner_char();
    }
}

// Scans a block of raw code into the current token. This is a scanner routine,
// but it is called by the parser.
int scan_block() {

    int count = 0;

    if(scanner_state->token->type == OBRACE) {

        int level = 1;
        add_string_char(scanner_state->token->str, '{');
        count++;

        while(level > 0) {
            int ch = get_scanner_char();
            if(ch == EOF) {
                scanner_state->token->type = ERROR;
                scanner_error("unexpected end of file in block");
                return 0;
            }
            else if(ch == '{')
                level++;
            else if(ch == '}')
                level--;

            add_string_char(scanner_state->token->str, ch);
            consume_scanner_char();
            count++;
        }
    }
    else {
        syntax_error("expected a code block but got a %s", tok_type_to_str(scanner_state->token->type));
        scanner_state->token->type = ERROR;
        return 0;
    }

    LOG(SLEVEL, "scanner: %d: %d: \"%s\" (BLOCK)", get_line_no(), get_col_no(), raw_string(scanner_state->token->str));
    scanner_state->token->type = BLOCK;
    return count;
}

const char* tok_type_to_str(TokenType type) {

    return (type == TOKENS) ? "TOKENS" :
    (type == GRAMMAR)       ? "GRAMMAR" :
    (type == SOURCE)        ? "SOURCE" :
    (type == HEADER)        ? "HEADER" :
    (type == BLOCK)         ? "BLOCK" :
    (type == SYMBOL)        ? "SYMBOL" :
    (type == COLON)         ? ":" :
    (type == SEMI)          ? ";" :
    (type == OBRACE)        ? "{" :
    (type == CBRACE)        ? "}" :
    (type == END_OF_INPUT)  ? "END OF INPUT" :
    (type == ERROR)         ? "ERROR" :
                              "UNKNOWN";
}
