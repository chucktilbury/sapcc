#ifndef _ERRORS_H
#define _ERRORS_H

#include "parser.h"

// Convience functions
void syntax_error(const char* fmt, ...);
void warning(const char* fmt, ...);
void fatal(const char* fmt, ...);

// Only the convience functions update these.
int get_errors();
int get_warnings();
void increment_errors();
void increment_warnings();


#endif /* _ERRORS_H */
