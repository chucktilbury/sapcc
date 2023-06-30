
#include "common.h"
#include "scanner.h"
#include "standard.h"

/**
 * @brief
 *     TokenType type;
 *     Str str;
 *     int line;
 *     int col;
 *
 *
 * @param tok
 */
static void print_token(Token* tok) {

    printf("tok: %s\t%s (%d)\t%d\t%d\n", raw_str(tok->str), tok_to_str(tok->type), tok->type, tok->line, tok->col);
}

int main() {

    open_scanner_file("../test/test1.sapcc");
    Token tok;

    while(true) {
        get_token(&tok);
        print_token(&tok);
        consume_token(NULL);
        if(tok.type == END_OF_INPUT)
            break;
    }
    return 0;
}