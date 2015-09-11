#include "array.h"
#include <stdlib.h>


void array_init(array_s *a, size_t initialSize) {
    a->data = (void *)malloc(initialSize * sizeof(void*));
    a->count = 0;
    a->size = initialSize;
}

void array_add(array_s *a, void* element) {
    if (a->count == a->size) {
        a->size *= 2;
        a->data = (void *)realloc(a->data, a->size * sizeof(void*));
    }
    a->data[a->count++] = element;
}

void array_free(array_s *a) {
    free(a->data);
    a->data = NULL;
    a->count = a->size = 0;
}