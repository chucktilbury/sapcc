/*
 * This is a framework for manipulating paths and file names in a portable
 * and transparent manner. It should always produce the name of an openable
 * file, based on the OS that the program was built upon.
 */
#ifndef _PATHS_H
#define _PATHS_H

#include "util.h"

// returns everything after the last '/' or '\\', depending on the OS.
Str* path_basename(Str* name);
// returns everything before the last '/'
Str* path_dirname(Str* name);
// returns true of the object specified by name can be stat() 'ed
bool path_exists(Str* name);
// if the name exists and it is a file, then return true
bool path_isfile(Str* name);
// if the name exists and it is a directory name, then return true
bool path_isdir(Str* name);
// Takes the strings in names and joins them as a path depending on the OS
Str* path_join(StrList* names);
// Split the name into a list of strings
StrList* path_split(Str* names);
// Uses the C realpath() library routine to get the absolute path name.
Str* path_abspath(Str* name);
// strip the ext, if it exists. if not return the original str
Str* path_stripext(Str* name);

#endif /* _PATHS_H */
