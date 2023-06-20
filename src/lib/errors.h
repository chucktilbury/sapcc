#ifndef _ERRORS_H
#define _ERRORS_H

void error(const char* fmt, ...);
void fatal(const char* fmt, ...);
int get_errors();

#define ERROR(fmt, ...) error(fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...) fatal(fmt, ##__VA_ARGS__)

#endif /* _ERRORS_H */
