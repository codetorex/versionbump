//
// Created by KALEM on 9/11/2015.
//

#ifndef VERSIONBUMP_ARRAY_H
#define VERSIONBUMP_ARRAY_H

#include <stddef.h>

typedef struct {
    void **data;
    size_t count;
    size_t size;
} array_s;

void array_init(array_s *a, size_t initialSize);
void array_add(array_s *a, void* element);
void array_free(array_s *a);

static inline void* array_get(array_s* a, int index)
{
    return a->data[index];
}

#endif //VERSIONBUMP_ARRAY_H
