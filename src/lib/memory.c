/**
 * @file memory.c
 *
 * @brief Interface to the GC library or the libc allocation routines.
 *
 */
#include "standard.h"
#include <string.h>

#include "errors.h"
#include "memory.h"
#ifdef USE_GC
#include <gc.h>
#endif

void* mem_alloc(size_t size) {

#ifndef USE_GC
    void* ptr = malloc(size);
#else
    void* ptr  = GC_MALLOC(size);
#endif

    if(ptr == NULL)
        fatal("Cannot allocate memory: %lu\n", size);

    memset(ptr, 0, size);
    return ptr;
}

void* mem_realloc(void* ptr, size_t size) {

#ifndef USE_GC
    void* nptr = realloc(ptr, size);
#else
    void* nptr = GC_REALLOC(ptr, size);
#endif

    if(nptr == NULL)
        fatal("Cannot reallocate memory: %lu\n", size);

    return nptr;
}

void mem_free(void* ptr) {

#ifndef USE_GC
    if(ptr != NULL)
        free(ptr);
    else {
        fprintf(stderr, "Attempt to free NULL pointer\n");
        exit(1);
    }
#else
    (void)ptr;
#endif
}

void* mem_dup_str(const char* str) {

    return mem_dup((void*)str, strlen(str) + 1);
}

void* mem_dup(void* ptr, size_t size) {

#ifndef USE_GC
    void* nptr = malloc(size);
#else
    void* nptr = GC_MALLOC(size);
#endif

    if(nptr == NULL)
        fatal("Cannot duplicate memory: %lu\n", size);

    memcpy(nptr, ptr, size);
    return nptr;
}
