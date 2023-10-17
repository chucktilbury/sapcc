#ifndef _LOGGER_H
#define _LOGGER_H

#include "util.h"
extern CmdLine cmd;

#define VERBOSITY() get_cmd_int(cmd, "verbo")
#define STREAM  stdout

#define LOG(n, fmt, ...) do { \
        if((n) <= VERBOSITY()) { \
            fprintf(STREAM, fmt, ##__VA_ARGS__); \
            fputc('\n', STREAM); \
        } \
    } while(0)


#endif /* _LOGGER_H */
