
#include "errors.h"
#include "parser.h"
#include "scanner.h"
#include "util.h"

CmdLine cmd;

int main(int argc, char** argv) {

    cmd = create_cmd_line("Simple As Possible Compiler Compiler.\n"
                          "Generate a parser and associated modules from a simple grammar file.");
    add_cmd(cmd, "-h", "help", "Show the help documentation.", NULL, CMD_HELP);
    // leaving this at 0 prints only warnings and errors.
    add_cmd(cmd, "-v", "verbo", "Set the verbosity level.", "0", CMD_INT);
    // Set the highest pass level. Setting it to 0 tests the scanner only.
    add_cmd(cmd, "", "file", "File name of the grammar to generate.", NULL, CMD_REQD | CMD_STR);
    parse_cmd_line(cmd, argc, argv);

    init_parser();

    parser();

#ifdef ENABLE_DUMP
    if(9 <= VERBOSITY()) {
        dump_parser();
    }
#endif

    if(1 <= VERBOSITY())
        printf("%s\n", get_errors() ? "failed" : "success");

    if(2 <= VERBOSITY())
        printf("\nstatistics:\nterminals: %d\nnon-terminals: %d\n", get_num_term(), get_num_nterm());

    return 0;
}
