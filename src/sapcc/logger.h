#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef ENABLE_LOGGER
#include "util.h"
extern CmdLine cmd;

#define STREAM  stdout

#define LOG(n, fmt, ...) do { \
        if((n) <= VERBOSITY()) { \
            fprintf(STREAM, fmt, ##__VA_ARGS__); \
            fputc('\n', STREAM); \
        } \
    } while(0)
#else
#define LOG(n, f, ...)
#endif

#define VERBOSITY() get_cmd_int(cmd, "verbo")

#endif /* _LOGGER_H */
