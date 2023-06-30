/**
 * @file strs.c
 *
 * @brief Various routines used to manipulate C strings as an object. These
 * strings are similar to strings in Pascal. The length is part of the string,
 * however, the string itself is still zero terminated like a C string. A data
 * structure is prepended to the string in order to track the memory allocated
 * for it.
 *
 */
#include "standard.h"
#include <stdarg.h>
#include <string.h>

#include "memory.h"
#include "strs.h"

/**
 * @brief Private string data structure.
 *
 */
struct _string_ {
    size_t len;
    size_t cap;
    char* buffer;
};

#define SIZE sizeof(struct _string_)
#define NOT_NULL(p) assert((p) != NULL)

static void cat_string(struct _string_* ptr, const char* str) {

    size_t len = strlen(str);
    if(ptr->len + len + 1 > ptr->cap) {
        while(ptr->len + len + 1 > ptr->cap)
            ptr->cap <<= 1;
        ptr->buffer = _realloc_mem(ptr->buffer, ptr->cap);
    }

    memcpy(&ptr->buffer[ptr->len], str, len + 1);
    ptr->len += len;
    ptr->buffer[ptr->len] = '\0';
}

/**
 * @brief Create a Str object from a const char buffer.
 *
 * @param str
 * @return Str*
 */
Str create_str(const char* str) {

    struct _string_* ptr = _alloc_obj(struct _string_);
    ptr->cap             = 0x01 << 3;
    ptr->len             = 0;
    ptr->buffer          = _alloc_array(char, ptr->cap);

    if(str != NULL && strlen(str) > 0)
        cat_string(ptr, str);

    return ptr;
}

/**
 * @brief Create a Str object using printf() style formatting.
 *
 * @param fmt
 * @param ...
 * @return Str*
 */
Str create_str_fmt(const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = _alloc_mem(len + 2);

    va_start(args, fmt);
    vsnprintf(str, len + 2, fmt, args);
    va_end(args);

    Str ptr = create_str(str);
    _free(str);

    return ptr;
}

/**
 * @brief Destroy a string. This is a no-op if GC is active.
 *
 * @param h
 */
void destroy_str(Str h) {

    NOT_NULL(h);
    _free(h->buffer);
    _free(h);
}

/**
 * @brief Add a character to the end of a string.
 *
 * @param str
 * @param ch
 * @return int
 */
int cat_str_char(Str ptr, int ch) {

    NOT_NULL(ptr);
    if(ptr->len + 1 >= ptr->cap) {
        ptr->cap <<= 1;
        ptr->buffer = _realloc_array(ptr->buffer, char, ptr->cap);
    }

    ptr->buffer[ptr->len] = ch;
    ptr->len++;
    ptr->buffer[ptr->len] = '\0';

    return ptr->len;
}

/**
 * @brief Append a literal string to the end of a Str object.
 *
 * @param ptr
 * @param str
 * @return int
 */
int cat_str_str(Str ptr, const char* str) {

    NOT_NULL(ptr);
    size_t len = strlen(str);

    if(ptr->len + len + 1 >= ptr->cap) {
        while(ptr->len + len + 1 >= ptr->cap)
            ptr->cap <<= 1;
        ptr->buffer = _realloc_array(ptr->buffer, char, ptr->cap);
    }

    memcpy(&ptr->buffer[ptr->len], str, len + 1);
    ptr->len += len;
    ptr->buffer[ptr->len] = '\x0';

    return ptr->len;
}

/**
 * @brief Append a formatted string to the end of a Str object.
 *
 * @param ptr
 * @param fmt
 * @param ...
 * @return int
 */
int cat_str_fmt(Str ptr, const char* fmt, ...) {

    NOT_NULL(ptr);
    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = _alloc_mem(len + 2);

    va_start(args, fmt);
    vsnprintf(str, len + 2, fmt, args);
    va_end(args);

    cat_str_str(ptr, str);
    _free(str);

    return ptr->len;
}

/**
 * @brief Strip the spaces from the beginning and the end of a Str object.
 *
 * @param ptr
 * @return Str*
 */
int strip_str(Str ptr) {

    NOT_NULL(ptr);
    int idx;

    for(idx = 0; isspace(ptr->buffer[idx]) && ptr->buffer[idx] != '\x0'; idx++) {
    }

    if(idx > 0)
        memmove(ptr->buffer, &ptr->buffer[idx], strlen(&ptr->buffer[idx]) + 1);

    for(idx = strlen(ptr->buffer) - 1; isspace(ptr->buffer[idx]) && idx > 0; idx--)
        ptr->buffer[idx] = 0;

    ptr->len = strlen(ptr->buffer);
    return ptr->len;
}

/**
 * @brief Truncate the string to zero length. This does not free the string
 * buffer, but it does write a zero at the beginning of the string.
 *
 * @param str
 */
void clear_str(Str ptr) {

    NOT_NULL(ptr);
    ptr->len       = 0;
    ptr->buffer[0] = 0;
}

/**
 * @brief Compares the literal string to the string object. If the object is
 * longer, then only compare the length of the literal string. If the compare
 * matches, then return zero, otherwise return a positive or negative value
 * same as strcmp() does.
 *
 * @param base
 * @param str
 * @return int
 */
int comp_str(Str ptr, const char* str) {

    NOT_NULL(ptr);
    return strncmp(ptr->buffer, str, strlen(str));
}

/**
 * @brief Make string uppercase
 *
 * @param str
 */
void upcase_str(Str ptr) {

    NOT_NULL(ptr);
    for(char* s = ptr->buffer; *s != '\0'; s++)
        *s = toupper(*s);
}

/**
 * @brief Make string lower case.
 *
 * @param str
 */
void downcase_str(Str ptr) {

    NOT_NULL(ptr);
    for(char* s = ptr->buffer; *s != '\0'; s++)
        *s = tolower(*s);
}

/**
 * @brief Make a copy of the string.
 *
 * @param str
 * @return Str*
 */
Str copy_str(Str ptr) {

    NOT_NULL(ptr);
    return create_str(ptr->buffer);
}

/**
 * @brief Return the number of characters in the string, excluding the
 * ending terminating null.
 *
 * @param ptr
 * @return size_t
 */
size_t len_str(Str ptr) {

    NOT_NULL(ptr);
    return ptr->len;
}

/**
 * @brief Return a C string from the data structure.
 *
 * @param h
 * @return const char*
 */
const char* raw_str(Str ptr) {

    NOT_NULL(ptr);
    return ptr->buffer;
}


#ifdef _TEST_STRINGS_
// build string:
// gcc -Wall -Wextra -D_TEST_STRINGS_ -DUSE_GC -g -o ts strs.c memory.c errors.c -lgc

int main() {

    Str s = create_str("create a string");
    printf("str: %s\n", raw_str(s));

    s = create_str_fmt("create a %s with %s", "string", "formatting");
    printf("str: %s\n", raw_str(s));

    cat_str_char(s, 'X');
    printf("str: %s\n", raw_str(s));

    cat_str_str(s, " <- an \"exx\"");
    printf("str: %s\n", raw_str(s));

    cat_str_fmt(s, " with %s with number: %d", "formatting", 1234);
    printf("str: %s\n", raw_str(s));

    s = create_str("  \t  this is before stripping    ");
    printf("B4 str: \"%s\"\n", raw_str(s));
    strip_str(s);
    printf("after str: \"%s\"\n", raw_str(s));
    clear_str(s);
    printf("clear str: \"%s\"\n", raw_str(s));

    cat_str_str(s, "this is a lower case string");
    printf("B4 str: \"%s\"\n", raw_str(s));
    upcase_str(s);
    printf("upcase str: \"%s\"\n", raw_str(s));
    downcase_str(s);
    printf("downcase str: \"%s\"\n", raw_str(s));

    s = copy_str(s);
    printf("copy of str: \"%s\"\n", raw_str(s));

    s = create_str("monkey patch the bacon");
    printf("compare strings \"%s\" and \"%s\" is %s\n", raw_str(s), "monkey patch the bacon",
           comp_str(s, "monkey patch the bacon") == 0 ? "true" : "false");

    printf("compare strings \"%s\" and \"%s\" is %s\n", raw_str(s), "monkey patch", comp_str(s, "monkey patch") == 0 ? "true" : "false");

    printf("compare strings \"%s\" and \"%s\" is %s\n", raw_str(s), "patch the bacon", comp_str(s, "patch the bacon") == 0 ? "true" : "false");

    printf("compare strings \"%s\" and \"%s\" is %s\n", raw_str(s), "Monkey patch", comp_str(s, "Monkey patch") == 0 ? "true" : "false");

    printf("string \"%s\" length is %lu\n", raw_str(s), len_str(s));

    return 0;
}

#endif

#if 0
/**
 * @brief Return the index of the first instance of the substring. If the
 * substring is not found then return a negative value.
 *
 * @param str
 * @param s
 * @return int
 */
int find_str(Str str, const char* s) {

    LOCAL(ptr, str);
    char* tmp = strstr(ptr->buffer, s);

    if(tmp != NULL)
        return (size_t)tmp - (size_t)ptr->buffer;
    else
        return -1;
}

/**
 * @brief Return a new string that contains the characters from the base
 * string that falls between the indexes, inclusive. If there are no
 * characters within the range, then return NULL.
 *
 * @param base
 * @param start
 * @param end
 * @return Str*
 */
Str clip_str(Str base, int start, int end) {

    LOCAL(ptr, base);
    Str retv = NULL;

    if(start < end && (size_t)start < base->len && (size_t)end < base->len) {
        retv = create_str(NULL);
        for(int idx = start; idx <= end; idx++)
            cat_str_char(retv, base->buffer[idx]);
    }

    return retv;
}

/**
 * @brief Shorten the string to the specified index where the character at
 * the index is the terminating zero of the string.
 *
 * @param str
 * @param idx
 * @return int
 */
int truncate_str(Str str, int idx) {

    LOCAL(ptr, str);
    if((size_t)idx < ptr->len) {
        ptr->len = idx;
        ptr->buffer[ptr->len] = '\0';
    }

    return ptr->len;
}


#endif