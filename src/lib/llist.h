/**
 * @file llist.h
 *
 * @brief Implement a single linked list functionality.
 *
 */
#ifndef _LLIST_H
#define _LLIST_H

typedef struct _llist_* LList;
typedef void* LListItem;

LList create_llist();
void append_llist(LList lst, void* data, size_t size, int type);
void prepend_llist(LList lst, void* data, size_t size, int type);
LListItem get_llist_item(LList lst, int index);
size_t get_llist_item_size(LListItem item);
int get_llist_item_type(LListItem item);

void remove_llist_item(LListItem item);
LList rebuild_llist(LList lst);

void push_llist(LList lst, void* data, size_t size, int type);
void pop_llist(LList lst);
LListItem peek_llist(LList lst);

LListItem reset_llist(LList lst);
LListItem iter_llist(LList lst);

#endif /* _LLIST_H */
