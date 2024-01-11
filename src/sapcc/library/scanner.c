/**
 * @file scanner.c
 * 
 * @brief This is the implemetation of the default example scanner. It 
 * implements scanning for keywords that are defined in the grammar and 
 * also default constructed tokens that are literal numbers and literal
 * strings. Also symbols and operators such as "!=" and "==". It is 
 * designed to be easy to change to match different requirements. The 
 * scanner that is implemented here is intended to scan the tokens as they
 * are defined for the Simple programming language. See the header file for
 * more information. 
 * 
 * In addition to the operators and keywords (which are defined as strings in 
 * the grammar), floating point numbers, symbols, and quoted strings are 
 * tokenized from the input. 
 * 
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-07-2024
 * @copyright Copyright (c) 2024
 */
#include "util.h"
#include "keywords.h"
#include "scanner.h"

static Token token;

/**
 * @brief Comments are not retuned by the scanner. This reads from the ';' and 
 * discards the data.
 */
static void eat_comment() {

    int ch;

    // the current char is a ';' when this is entered
    while(true) {
        ch = consume_char();
        if(ch == '\n' || ch == '\r' || ch == EOF)
            break;
    }
}

/**
 * @brief All numbers in Simple are floating point with an optional mantissa 
 * and exponent. Any string that strtod() recognizes is valid. If the first 
 * character is a '0' then it must be followed by a '.' or a non-digit. Leading
 * '0' in a number is a syntax error.
 */
static void scan_number() {

}

/**
 * @brief Single and multi-character operators as defined in the grammar.
 */
static void scan_operator() {

    int ch = get_char();

    // when this is entered, the current char is the first char of the operator
    switch(ch) {
        // single character operators
        case '^':   
            token.type = TOK_POW;       
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '(':   
            token.type = TOK_OPAREN;    
            add_string_char(token.str, ch);
            consume_char();
            return;
        case ')':   
            token.type = TOK_CPAREN;    
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '{':   
            token.type = TOK_OCBRACE;    
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '}':   
            token.type = TOK_CCBRACE;    
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '[':   
            token.type = TOK_OSBRACE;  
            add_string_char(token.str, ch);
            consume_char();
            return;
        case ']':   
            token.type = TOK_CSBRACE;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '.':
            token.type = TOK_DOT;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case ',':
            token.type = TOK_COMMA;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '@':
            token.type = TOK_AMPER;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case ':':
            token.type = TOK_COLON;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '&':
            token.type = TOK_AND;
            add_string_char(token.str, ch);
            consume_char();
            return;
        case '|':
            token.type = TOK_OR;
            add_string_char(token.str, ch);
            consume_char();
            return;

        // multi-character operators
        case '<': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_LTOE;
                }
                else 
                    token.type = TOK_LT;
            }
            return;
        case '>': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_GTOE;
                }
                else 
                    token.type = TOK_GT;
            }
            return;
        case '=': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_EQU;
                }
                else 
                    token.type = TOK_ASSIGN;
            }
            return;
        case '+': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_ADD_ASSIGN;
                }
                else 
                    token.type = TOK_ADD;
            }
            return;
        case '-': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_SUB_ASSIGN;
                }
                else 
                    token.type = TOK_SUB;
            }
            return;
        case '*': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_MUL_ASSIGN;
                }
                else 
                    token.type = TOK_MUL;
            }
            return;
        case '/': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_DIV_ASSIGN;
                }
                else 
                    token.type = TOK_DIV;
            }
            return;
        case '%': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_MOD_ASSIGN;
                }
                else 
                    token.type = TOK_MOD;
            }
            return;
        case '!': {
                add_string_char(token.str, ch);
                ch = consume_char();
                if(ch == '=') {
                    add_string_char(token.str, ch);
                    consume_char();
                    token.type = TOK_NEQU;
                }
                else 
                    token.type = TOK_NOT;
            }
            return;
    }
}

/**
 * @brief A word is defined as [a-zA-Z_][0-9a-zA-Z_]*. The word is first read
 * and then it is checked to see if it is a keyword. Keywords and not case-
 * sensitive.
 */
static void scan_word() {

    int ch;

    // current char is the first letter of the word when this is entered
    while(true) {
        ch = get_char();
        if(isalnum(ch) || ch == '_') {
            add_string_char(token.str, ch);
            consume_char();
        }
        else 
            break;
    }
}

/**
 * @brief Mark the token with the file name and the line number.
 */
static void finish_token() {

    token.line_no = get_line_no();
    token.col_no = get_col_no();
    token.fname = get_fname(); // simple const char*
}

/**
 * @brief Allocate the data structures that the scanner uses. This function
 * must be called before any characters are scanned.
 * 
 * 
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @date 01-10-2024
 * @version 0.0
 * @copyright Copyright (c) 2024
 */
void init_scanner() {

    memset(&token, 0, sizeof(Token));
    token.str = create_string(NULL);
}

/**
 * @brief This function reads a token from the input stream and returns in in 
 * a pointer to a global static Token data structure. When the token is read, 
 * a deep copy is performed to preserve the value. This keeps us from having 
 * to recompose the data structhre every time a token is read.
 * 
 * @return Token* 
 * 
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @date 01-10-2024
 * @version 0.0
 * @copyright Copyright (c) 2024
 */
Token* scan_token() {

    bool finished = false;
    int ch;

    clear_string(token.str);    
    while(!finished) {
        ch = get_char();

        // skip whitespace. line counting is done elsewhere
        if(isspace(ch)) {
            continue;
        }
        // comment precursor
        else if(ch == ';') {
            eat_comment();
        }
        // scan a number and return it
        else if(isdigit(ch)) {
            scan_number();
            finished = true;
        }
        // scan an operator and return it
        else if(ispunct(ch)) {
            scan_operator();
            finished = true;
        }
        // symbols and keywords start with a letter
        else if(isalpha(ch)) {
            scan_word();
            finished = true;
        }
        // end of input has been reached
        else {
            token.type = END_OF_INPUT;
            return &token;  // do not update the line, etc.
        }
    }

    finish_token();
}

