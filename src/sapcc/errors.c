
#include <stdarg.h>

#include "parser.h"
#include "scanner.h"
#include "util.h"

static int errors = 0;
static int warnings = 0;

void syntax_error(const char* fmt, ...) {

    va_list args;

    if(get_line_no() > 0) {
        fprintf(stderr, "Syntax Error: %s:%d:%d: ", get_fname(), get_line_no(),
                get_col_no());
    }
    else {
        fprintf(stderr, "Syntax Error: ");
    }

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    errors++;
    fputc('\n', stderr);

    // TODO: error recovery.
}

void warning(const char* fmt, ...) {

    va_list args;

    if(get_line_no() > 0)
        fprintf(stderr, "Warning: %s:%d:%d: ", get_fname(), get_line_no(), get_col_no());
    else
        fprintf(stderr, "Warning: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    warnings++;
    fputc('\n', stderr);
}

void fatal(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "Fatal error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    errors++;
    fputc('\n', stderr);
}


// Only the convience functions update these.
int get_errors() {

    return errors;
}

int get_warnings() {

    return warnings;
}
