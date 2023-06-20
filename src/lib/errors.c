#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

static int errors = 0;

void error(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    errors++;
}

void fatal(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "fatal error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    errors++;
    exit(1);
}

int get_errors() {

    return errors;
}
