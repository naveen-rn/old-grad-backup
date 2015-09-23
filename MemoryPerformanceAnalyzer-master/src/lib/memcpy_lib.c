#include <stdio.h>
#include "memcpy_lib.h"

void *memcpy_naive
(void *dest, void *src, size_t size) {
    char* src_8 = (char*) src;
    char* dest_8 = (char*) dest;
    while(size--) {
        *dest_8++ = *src_8++;
    }
}

void *memcpy_array
(void *dest, void *src, size_t size) {
    size_t i;
    for (i = 0; i < size; i++) {
        //dest[i] = src[i];
    }
}

int get
(const int*const src, const size_t index) {
    return src[index];
}

int set
(int*const dest, const size_t index, const int value) {
    dest[index] = value;
}

void *memcpy_getset
(void *dest, void *src, size_t size) {
    size_t i;
    for (i = 0; i < size; i++) {
        set( dest, i, get(src, i) );
    }
}
