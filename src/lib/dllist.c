/**
 * @file list.c
 *
 * @brief Linked list implementation. This is a fairly complete implementation
 * that includes a stack and iteration interfaces. The list nodes are
 * accessible internally using tricky pointer arithmetic. This requires the
 * memory interface module and also supports GC.
 *
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dllist.h"
#include "memory.h"

/**
 * @brief Private data structure that holds the actual data.
 *
 */
typedef struct _list_elem_ {
    int type;
    size_t size;
    struct _list_elem_* next;
    struct _list_elem_* prev;
    // unsigned char data; is implied by the pointer arithmetic
} ListElem;

/**
 * @brief Public data structure that implements lists.
 *
 */
typedef struct _list_ {
    ListElem* first;
    ListElem* last;
    ListElem* crnt;
    size_t len;
} List;

#define ELEM_SIZE sizeof(ListElem)
#define NOTNULL(p) assert((p) != NULL)
#define CAST_LST(p) ((struct _list_*)(p))
#define IMPORT_ELEM(p)  ((ListElem*)(((unsigned long)(p)) - ELEM_SIZE))
#define EXPORT_ELEM(p)  ((void*)(((unsigned long)(p)) + ELEM_SIZE))
#define RETURN_PTR(p) return (DLList)(p);

#define LOCAL_LST(n, p) \
    NOTNULL(p);         \
    List* n = (List*)(p)

#define LOCAL_ELEM(n, p) \
    NOTNULL(p);          \
    ListElem* n = IMPORT_ELEM(p)

/**
 * @brief Create a list object
 *
 * @return DLList
 */
DLList create_lst() {

    List* lst = _alloc_obj(List);
    RETURN_PTR(lst);
}

static void free_elem(ListElem* elem) {

    if(elem != NULL) {
        _free(elem);
    }
}

/**
 * @brief Destroy a list object along with its data.
 *
 * @param lst
 */
void destroy_lst(DLList lst) {

    LOCAL_LST(l, lst);

    ListElem* elem;
    ListElem* next;

    for(elem = l->first; elem != NULL; elem = next) {
        next = elem->next;
        free_elem(elem);
    }

    _free(lst);
}

static ListElem* create_elem(void* data, size_t size, int type) {

    NOTNULL(data);
    ListElem* elem = _alloc_mem(ELEM_SIZE + size);
    elem->size     = size;
    elem->type     = type;
    memcpy(EXPORT_ELEM(elem), data, size);

    // note that _alloc_obj() clears the memory.
    return elem;
}

/**
 * @brief Append data to the end of the list.
 *
 * @param lst
 * @param data
 * @param size
 * @param type
 */
void append_lst(DLList lst, void* data, size_t size, int type) {

    NOTNULL(data);
    LOCAL_LST(l, lst);
    ListElem* elem = create_elem(data, size, type);

    if(l->last != NULL) {
        elem->prev    = l->last;
        l->last->next = elem;
    }
    else {
        l->first = elem;
        l->crnt  = elem;
    }

    l->last = elem;
    l->len++;
}

/**
 * @brief Add data to the beginning of the list.
 *
 * @param lst
 * @param data
 * @param size
 * @param type
 */
void prepend_lst(DLList lst, void* data, size_t size, int type) {

    NOTNULL(data);
    LOCAL_LST(l, lst);
    ListElem* elem = create_elem(data, size, type);

    if(l->first != NULL) {
        elem->next     = l->first;
        l->first->prev = elem;
    }
    else {
        l->last = elem;
        l->crnt = elem;
    }

    l->first = elem;
    l->len++;
}

// if flag is true the insert after, else insert before
/**
 * @brief Insert data into the list, handling all of the cases of the insert
 * point being at the beginning or end of the list as well as if the list is
 * empty. If the flag is set, then the item is inserted after the given
 * element. If the flag is clear, then the new element is inserted where the
 * given list element is and that element is moved toward the end of the list.
 *
 * @param lst
 * @param elem
 * @param ptr
 * @param size
 * @param type
 * @param flag
 */
void insert_lst(DLList lst, void* elem, void* ptr, size_t size, int type, bool flag) {

    NOTNULL(ptr);
    LOCAL_ELEM(e, elem);
    ListElem* next;
    ListElem* prev;

    // insert after node
    if(flag) {
        if(e->next == NULL) {
            append_lst(lst, ptr, size, type);
            return;
        }
        else {
            next = e->next;
            prev = e->next->prev;
        }
    }
    // insert before node
    else {
        if(e->prev == NULL) {
            prepend_lst(lst, ptr, size, type);
            return;
        }
        else {
            next = e->prev->next;
            prev = e->prev;
        }
    }

    ((struct _list_*)lst)->len++;
    ListElem* nele = create_elem(ptr, size, type);
    nele->next     = next;
    nele->prev     = prev;

    next->prev = nele;
    prev->next = nele;
}

/**
 * @brief Insert the data given an integer index. If the index is negative,
 * then the count is from the end of the list instead of the beginning.
 *
 * @param lst
 * @param index
 * @param ptr
 * @param size
 * @param type
 * @param flag
 */
void insert_lst_idx(DLList lst, int index, void* ptr, size_t size, int type, bool flag) {

    void* e = get_elem(lst, index);
    insert_lst(lst, e, ptr, size, type, flag);
}

/**
 * @brief Return a pointer to the element that is indicated by the index. If
 * the index is negative then count from the end of the list. For example, if
 * the index is -1 then return the last item in the list. If the index is 0
 * then return the first item of the list. If the list is empty then return
 * NULL.
 *
 * @param lst
 * @param index
 * @return void*
 */
void* get_elem(DLList lst, int index) {

    LOCAL_LST(l, lst);
    ListElem* e;

    int count = 0;
    if(index >= 0) {
        e = l->first;
        for(; e != NULL && count < index; count++)
            e = e->next;
    }
    else {
        e = l->last;
        for(count = -1; e != NULL && count > index; count--)
            e = e->prev;
    }

    if(e == NULL)
        return NULL;
    else
        return EXPORT_ELEM(e);
}

/**
 * @brief If the element is a member of the list then this will return the
 * allocated size of the data. Otherwise, it returns garbage.
 *
 * @param elem
 * @return size_t
 */
size_t get_elem_size(void* elem) {

    NOTNULL(elem);
    return IMPORT_ELEM(elem)->size;
}

/**
 * @brief Return the item's type that was specified when the item was created.
 *
 * @param elem
 * @return int
 */
int get_elem_type(void* elem) {

    NOTNULL(elem);
    return IMPORT_ELEM(elem)->type;
}

/**
 * @brief Get the list length.
 *
 * @param lst
 * @return size_t
 */
size_t get_lst_len(DLList lst) {

    return ((struct _list_*)lst)->len;
}

/**
 * @brief Delete the specified item from the list, as specified using an
 * index. Does not account for crnt item, so items cannot be deleted while
 * iterating the list.
 *
 * @param lst
 * @param index
 */
void remove_lst_idx(DLList lst, int index) {

    remove_lst(lst, (void*)get_elem(lst, index));
}

/**
 * @brief Delete the item as specified by the data element. Does not account
 * for the crnt element.
 *
 * @param lst
 * @param elem
 */
void remove_lst(DLList lst, void* elem) {

    LOCAL_LST(l, lst);
    LOCAL_ELEM(e, elem);

    // first in a not-empty list
    if(e->prev == NULL && e->next != NULL) {
        l->first       = e->next;
        l->first->prev = NULL;
    }
    // last in a not-empty list
    else if(e->next == NULL && e->prev != NULL) {
        l->last       = e->prev;
        l->last->next = NULL;
    }
    // only element in the list
    else if(e->next == NULL && e->prev == NULL) {
        l->first = NULL;
        l->last  = NULL;
        l->crnt  = NULL;
    }
    // not first or last in a non-empty list
    else {
        // clarity is king
        ListElem* next = e->next;
        ListElem* prev = e->prev;
        next->prev     = prev;
        prev->next     = next;
    }
    free_elem(e);
    l->len--;
}

/**
 * @brief Add the data to the beginning of the list as a stack.
 *
 * @param lst
 * @param ptr
 * @param size
 * @param type
 */
void push_lst(DLList lst, void* ptr, size_t size, int type) {

    prepend_lst(lst, ptr, size, type);
}

/**
 * @brief Peek at the top of the stack and return the item there.
 *
 * @param lst
 * @return void*
 */
void* peek_lst(DLList lst) {

    LOCAL_LST(l, lst);
    return EXPORT_ELEM(l->first);
}

/**
 * @brief Remove the top item on the stack and destroy it.
 *
 * @param lst
 */
void pop_lst(DLList lst) {

    LOCAL_LST(l, lst);
    ListElem* tmp = l->first;
    l->first      = l->first->next;
    if(l->first != NULL)
        l->first->prev = NULL;
    else {
        l->last = NULL;
        l->crnt = NULL;
    }
    free_elem(tmp);
}

/**
 * @brief Reset the current pointer in the data structure to the beginning
 * of the list in preparation for iterating it. Use as the first expression
 * in a for() clause. Returns the first item in the list.
 *
 * @param lst
 * @return void*
 */
void* reset_lst(DLList lst) {

    LOCAL_LST(l, lst);
    l->crnt = l->first;
    return EXPORT_ELEM(l->crnt);
}

/**
 * @brief First increment the crnt pointer and then return the pointer. This
 * expects that reset was called before any call to iterate. It is not
 * possible to add or delete items from a list while iterating it. If that is
 * needed, then create a separate list and add items based on the criteria.
 *
 * @param lst
 * @return void*
 */
void* iterate_lst(DLList lst) {

    LOCAL_LST(l, lst);
    if(l->crnt != NULL)
        l->crnt = l->crnt->next;

    if(l->crnt != NULL)
        return EXPORT_ELEM(l->crnt);
    else
        return NULL;
}

/*
 * Highly contrived sanity test.
 */
#ifdef _TEST_LISTS_
// build string:
// gcc -Wall -Wextra -D_TEST_LISTS_ -g -o l dllist.c memory.c

typedef DLList int_lst_t;

#define create() List* lst = create_lst()
#define destroy() destroy_lst(lst)

#define insert(i, f) insert_lst_idx(lst, i, &val, sizeof(int), 124, f)
#define remove(i) remove_lst_idx(lst, i)
#define push() push_lst(lst, &val, sizeof(int), 123)
#define pop() pop_lst(lst)
#define peek() peek_lst(lst)

#define reset() reset_lst(lst)
#define iterate() iterate_lst(lst)

#define show() show_list(lst)

void show_list(DLList lst) {

    int count = 0;

    for(int* x = reset(); x != NULL; x = iterate())
        printf("%3d. value: %d (%d)\n", count++, *x, get_elem_type((void*)x));
    printf("\n");
}

int main() {

    create();
    int val = 0;

    val = 12;
    push();
    val = 1;
    push();
    val = 23;
    push();
    val = 82;
    push();
    val = 99;
    push();
    show();

    printf("insert 76 after index 2\n");
    val = 76;
    insert(2, true);
    show();

    printf("insert 54 at index 3\n");
    val = 54;
    insert(3, false);
    show();

    printf("remove index 0\n");
    remove(0);
    show();

    printf("remove index 5\n");
    remove(5);
    show();

    printf("remove index 3\n");
    remove(3);
    show();

    val = 34;
    printf("insert 34 at beginning\n");
    insert(0, 0);
    show();

    val = 43;
    printf("insert 43 at end\n");
    insert(-1, 1);
    show();

    destroy();
}

#endif
