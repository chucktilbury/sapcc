/**
 * @file strs.h
 *
 * @brief Routines to manipulate strings as an object, rather than as a raw
 * string in C. The string object is accessed through an opaque handle.
 *
 */
#ifndef _STRS_H
#define _STRS_H

#include <stddef.h> // for size_t type

/**
 * @brief Opaque handle for string object.
 *
 */
typedef const char* Str;

/**
 * @brief Public interface.
 */
Str create_str(const char* str);
Str create_str_fmt(const char* fmt, ...);
void destroy_str(Str h);
int cat_str_char(Str h, int ch);
int cat_str_str(Str h, const char* str);
int cat_str_fmt(Str h, const char* fmt, ...);
int strip_str(Str h);

void clear_str(Str h);
void upcase_str(Str h);
void downcase_str(Str h);
Str copy_str(Str h);
int comp_str(Str h, const char* str);
size_t len_str(Str h);
const char* raw_str(Str h);

// int truncate_str(Str h, int idx);
// int find_str(Str h, const char* s);
// Str clip_str(Str h, int start, int end);

#endif
