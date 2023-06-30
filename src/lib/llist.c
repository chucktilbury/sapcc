/**
 * @file llist.c
 *
 * @brief Implementation file for single-linked lists.
 *
 */
#include "standard.h"
#include <string.h>

#include "llist.h"
#include "memory.h"

struct _llist_item_ {
    int type;
    size_t size;
    bool active;
    struct _llist_item_* next;
    char data[0];
};

struct _llist_ {
    struct _llist_item_* first;
    struct _llist_item_* last;
    struct _llist_item_* crnt;
};

#define SIZE sizeof(struct _llist_item_)
#define NOTNULL(p) assert((p) != NULL)

#define ALLOC_ITEM(name, size) struct _llist_item_* name = _alloc_mem((size) + SIZE)
#define IMPORT_ITEM(p) ((struct _llist_item_*)(((unsigned long)(p)) - SIZE))
#define EXPORT_ITEM(p) (((p) != NULL) ? ((void*)(((unsigned long)(p)) + SIZE)) : NULL)
#define RETURN_ITEM(p) return EXPORT_ITEM(p)
#define LOCAL_ITEM(name, ptr) \
    NOTNULL(ptr);             \
    struct _llist_item_* name = IMPORT_ITEM(ptr)

#define ALLOC_LST(name) struct _llist_* name = _alloc_obj(struct _llist_);
#define LOCAL_LST(name, ptr) \
    NOTNULL(ptr);            \
    struct _llist_* name = (struct _llist_*)(ptr)

/**
 * @brief Create a item object
 *
 * @param data
 * @param size
 * @param type
 * @return struct _llist_item_*
 */
static struct _llist_item_* create_item(void* data, size_t size, int type) {

    ALLOC_ITEM(ptr, size);
    ptr->type   = type;
    ptr->size   = size;
    ptr->active = true;

    memcpy(&ptr->data[0], data, size);
    return ptr;
}

/**
 * @brief Create a llist object
 *
 * @return LList
 */
LList create_llist() {

    ALLOC_LST(ptr);
    return (LList)ptr;
}

/**
 * @brief Append data to the linked list.
 *
 * @param lst
 * @param data
 * @param size
 * @param type
 */
void append_llist(LList lst, void* data, size_t size, int type) {

    LOCAL_LST(ptr, lst);
    struct _llist_item_* item = create_item(data, size, type);

    if(ptr->last != NULL)
        ptr->last->next = item;
    else {
        ptr->first = item;
        ptr->crnt  = item;
    }
    ptr->last = item;
}

/**
 * @brief Prepend data to the linked list.
 *
 * @param lst
 * @param data
 * @param size
 * @param type
 */
void prepend_llist(LList lst, void* data, size_t size, int type) {

    LOCAL_LST(ptr, lst);
    struct _llist_item_* item = create_item(data, size, type);

    if(ptr->first == NULL) {
        ptr->last = item;
        ptr->crnt = item;
    }
    item->next = ptr->first; // could be NULL
    ptr->first = item;
}

/**
 * @brief Get the llist item object
 *
 * @param lst
 * @param index
 * @return LListItem
 */
LListItem get_llist_item(LList lst, int index) {

    assert(index >= 0);
    LOCAL_LST(ptr, lst);
    struct _llist_item_* item = ptr->first;

    for(int i = 0; item != NULL && i < index; i++)
        item = item->next;

    return item;
}

/**
 * @brief Get the llist item size object
 *
 * @param item
 * @return size_t
 */
size_t get_llist_item_size(LListItem item) {

    LOCAL_ITEM(ptr, item);
    return ptr->size;
}

/**
 * @brief Get the llist item type object
 *
 * @param item
 * @return int
 */
int get_llist_item_type(LListItem item) {

    LOCAL_ITEM(ptr, item);
    return ptr->type;
}

/**
 * @brief Remove an item from the list.
 *
 * @param item
 */
void remove_llist_item(LListItem item) {

    LOCAL_ITEM(ptr, item);
    ptr->active = false;
}

/**
 * @brief Rebuild the list and actually remove deleted items.
 *
 * @param lst
 * @return LList
 */
LList rebuild_llist(LList lst) {

    LOCAL_LST(ptr, lst);
    ALLOC_LST(nptr);

    for(struct _llist_item_* item = ptr->first; item != NULL; item = item->next) {
        if(item->active == true) {
            if(nptr->last != NULL)
                nptr->last->next = item;
            else {
                nptr->first = item;
                nptr->crnt  = item;
            }
            nptr->last = item;
        }
        else
            _free(item);
    }

    return (LList)nptr;
}

/**
 * @brief Push data on the list as if it's a stack.
 *
 * @param lst
 * @param data
 * @param size
 * @param type
 */
void push_llist(LList lst, void* data, size_t size, int type) {

    prepend_llist(lst, data, size, type);
}

/**
 * @brief Remove the item at the top of the stack. Does not return it because it
 * controls the memory allocated to it.
 *
 * @param lst
 */
void pop_llist(LList lst) {

    LOCAL_LST(ptr, lst);
    if(ptr->first != NULL) {
        struct _llist_item_* item = ptr->first;
        ptr->first                = item->next;
        if(ptr->first != NULL) {
            _free(item);
        }
        else {
            ptr->last = NULL;
            ptr->crnt = NULL;
        }
    }
    else {
        ptr->last = NULL;
        ptr->crnt = NULL;
    }
}

/**
 * @brief Return the item at the top of the stack.
 *
 * @param lst
 * @return LListItem
 */
LListItem peek_llist(LList lst) {

    LOCAL_LST(ptr, lst);
    struct _llist_item_* item;
    if(ptr->first != NULL) {
        item = ptr->first;
        if(item == NULL) {
            ptr->last = NULL;
            ptr->crnt = NULL;
        }
        RETURN_ITEM(item);
    }
    else {
        ptr->last = NULL;
        ptr->crnt = NULL;
        return NULL;
    }
}

/**
 * @brief Reset the list so that a call to iter_llist() returns the second item. This
 * function returns the first item.
 *
 * @param lst
 * @return LListItem
 */
LListItem reset_llist(LList lst) {

    LOCAL_LST(ptr, lst);
    ptr->crnt = ptr->first;

    RETURN_ITEM(ptr->crnt);
}

/**
 * @brief Iterated through the list. Returns NULL at the end.
 *
 * @param lst
 * @return LListItem
 */
LListItem iter_llist(LList lst) {

    LOCAL_LST(ptr, lst);
    struct _llist_item_* item = ptr->crnt;
    if(item != NULL)
        ptr->crnt = item->next;
    else {
        ptr->last  = NULL;
        ptr->crnt  = NULL;
        ptr->first = NULL;
    }

    RETURN_ITEM(ptr->crnt);
}

#ifdef _TEST_LLIST_
/**
 * @brief Sanity test.
 *
 *  Build string:
 *  gcc -Wall -Wextra -D_TEST_LLIST_ -DUSE_GC -g -o tl llist.c memory.c errors.c -lgc
 */
#include <string.h>

void dump(LList lst, const char* name) {

    printf("--- %s ---\n", name);
    const char* ptr = reset_llist(lst);
    while(ptr != NULL) {
        printf("value: %s (%d)\n", ptr, get_llist_item_type((void*)ptr));
        ptr = iter_llist(lst);
    }
    printf("\n");
}

int main() {

    char buffer[1024];
    int num   = 100;
    LList lst = create_llist();

    strcpy(buffer, "this is a string");
    append_llist(lst, buffer, strlen(buffer), num++);
    dump(lst, "appended one");

    strcpy(buffer, "this is another string");
    append_llist(lst, buffer, strlen(buffer), num++);
    dump(lst, "appended second");

    strcpy(buffer, "prepended string");
    prepend_llist(lst, buffer, strlen(buffer), num++);
    dump(lst, "prepended one");

    strcpy(buffer, "pushed string 1");
    push_llist(lst, buffer, strlen(buffer), num++);
    strcpy(buffer, "pushed string 2");
    push_llist(lst, buffer, strlen(buffer), num++);
    strcpy(buffer, "pushed string 3");
    push_llist(lst, buffer, strlen(buffer), num++);
    dump(lst, "pushed 3");

    pop_llist(lst);
    dump(lst, "popped 1");

    strcpy(buffer, "append string 1");
    append_llist(lst, buffer, strlen(buffer), num++);
    strcpy(buffer, "append string 2");
    append_llist(lst, buffer, strlen(buffer), num++);
    dump(lst, "appended 2");

    return 0;
}

#endif