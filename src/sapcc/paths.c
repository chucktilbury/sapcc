
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <fcntl.h>

#include "paths.h"

// returns everything after the last '/' or '\\', depending on the OS.
Str* path_basename(Str* name) {

    char* str = _DUP_STR(raw_string(name));

#if __unix__
    // gcc #defines __unix__ 1
    char* tpt = strrchr(str, '/');
#else
    // for windoze
    char* tpt = strrchr(str, '\\');
#endif

    if(tpt != NULL)
        tpt++;

    Str* s = create_string(tpt);
    _FREE(str);

    return s;
}

// returns everything before the last '/'
Str* path_dirname(Str* name) {

    char* str = _DUP_STR(raw_string(name));

#if __unix__
    // gcc "#define __unix__ 1" for Linux
    char* tpt = strrchr(str, '/');
#else
    // windoze is something else
    char* tpt = strrchr(str, '\\');
#endif

    if(tpt != NULL) {
        tpt++;
        *tpt = '\0';
    }

    Str* s = create_string(str);
    _FREE(str);

    return s;
}

// returns true of the object specified by name can be stat() 'ed
bool path_exists(Str* name) {

    struct stat statbuf;

    if(!stat(raw_string(name), &statbuf))
        return true;
    else
        return false;
}

// if the name exists and it is a file, then return true
bool path_isfile(Str* name) {

    struct stat statbuf;

    if(!stat(raw_string(name), &statbuf))
        if((statbuf.st_mode & S_IFMT) == S_IFREG)
            return true;

    return false;
}

// if the name exists and it is a directory name, then return true
bool path_isdir(Str* name) {

    struct stat statbuf;

    if(!stat(raw_string(name), &statbuf))
        if((statbuf.st_mode & S_IFMT) == S_IFDIR)
            return true;

    return false;
}

// Takes the strings in names and joins them as a path depending on the OS
Str* path_join(StrList* names) {

    PtrListIter* ptr = init_list_iterator(names);
    Str* str = create_string(NULL);
    Str* s;
    iterate_list(ptr, &s);
    add_string_Str(str, s);
    while(iterate_list(ptr, &s)) {
#if __unix__
        add_string_char(str, '/');
#else
        add_string_char(str, '\\');
#endif
        add_string_Str(str, s);
    }

    return str;
}

// Split the name into a list of strings
StrList* path_split(Str* names) {

    char* str = _DUP_STR(raw_string(names));
    StrList* lst = create_string_list();
    char *head = str, *tail;

    tail = strchr(head, '/');
    if(tail != NULL) {
        *tail = '\0';
        add_string_list(lst, create_string(head));
        head = ++tail;
    }
    else {
        add_string_list(lst, create_string(head));
        head = ++tail;
        return lst;
    }

    while(true) {
        tail = strchr(head, '/');
        if(tail != NULL)
            *tail = '\0';
        else
            break;
        add_string_list(lst, create_string(head));
        head = ++tail;
    }

    return lst;
}

// Uses the C realpath() library routine to get the absolute path name.
Str* path_abspath(Str* name) {

    char* buf = _ALLOC(PATH_MAX); // GCC specific define

    realpath(raw_string(name), buf); // other C compilers?
    Str* s = create_string(buf);

    _FREE(buf);

    return s;
}

Str* path_stripext(Str* name) {

    char* str = _DUP_STR(raw_string(name));
    char* tpt = strrchr(str, '.');
    if(tpt != NULL)
        *tpt = '\0';

    Str* s = create_string(str);
    _FREE(str);

    return s;
}
