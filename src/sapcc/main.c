
#include "parser.h"
#include "scanner.h"
#include "util.h"

CmdLine cmd;
/*
// leave this dead source code in for validating changes.
int test_scanner(Parser* ptr) {

    int finished = 0;

    while(!finished) {
        Token* tok = get_token(ptr->scanner);
        if(len_string(tok->str) > 0)
            printf("%s:%lu:%lu:\t%s: %s\n", ptr->scanner->fname, ptr->scanner->line, ptr->scanner->col,
                   tok_type_to_str(tok->type), raw_string(tok->str));
        else
            printf("%s:%lu:%lu:\t%s\n", ptr->scanner->fname, ptr->scanner->line, ptr->scanner->col, tok_type_to_str(tok->type));

        if(tok->type == END_OF_INPUT)
            finished++;
        consume_token(ptr->scanner);
    }

    return 0;
}
*/
int main(int argc, char** argv) {

    cmd = create_cmd_line("Simple As Possible Compiler Compiler.\n"
                                  "Generate a parser and associated modules from a simple grammar file.");
    add_cmd(cmd, "-h", "help", "Show the help documentation.", NULL, CMD_HELP);
    // leaving this at 0 prints only warnings and errors.
    add_cmd(cmd, "-v", "verbo", "Set the verbosity level.", "0", CMD_INT);
    // Set the highest pass level. Setting it to 0 tests the scanner only.
    add_cmd(cmd, "", "file", "File name of the grammar to generate.", NULL, CMD_REQD | CMD_STR);
    parse_cmd_line(cmd, argc, argv);

    int success;
    init_parser();

    success = parser();

    if(10 <= VERBOSITY()) {
        dump_parser();
    }

    if(1 <= VERBOSITY())
        printf("%s\n", success? "failed": "success");

    if(2 <= VERBOSITY())
        printf("\nstatistics:\nterminals: %d\nnon-terminals: %d\n",
               get_num_term(), get_num_nterm());

    return success;
}
