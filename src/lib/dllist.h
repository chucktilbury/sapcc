/**
 * @file list.h
 *
 * @brief List header. Fairly complete double linked list. This is intended
 * to be used with a pre-processor wrapper that automatically casts the
 * intended data back and forth. See the test code at the bottom of list.c
 * to see a simple contrived example example.
 */
#ifndef _DLLIST_H
#define _DLLIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Lists are accessed using an opaque handle.
 */
typedef void* DLList;

/**
 * @brief Public interface.
 */
DLList create_lst();
void destroy_lst(DLList lst);

void append_lst(DLList lst, void* ptr, size_t size, int type);
void prepend_lst(DLList lst, void* ptr, size_t size, int type);
void insert_lst_idx(DLList lst, int index, void* ptr, size_t size, int type, bool flag);
void insert_lst(DLList lst, void* elem, void* ptr, size_t size, int type, bool flag);

void* get_elem(DLList lst, int index);
size_t get_elem_size(void* elem);
int get_elem_type(void* elem);
size_t get_lst_len(DLList lst);

void remove_lst_idx(DLList lst, int index);
void remove_lst(DLList lst, void* elem);

void push_lst(DLList lst, void* elem, size_t size, int type);
void pop_lst(DLList lst);
void* peek_lst(DLList lst);

void* reset_lst(DLList lst);
void* iterate_lst(DLList lst);

#endif /* _LIST_H */
