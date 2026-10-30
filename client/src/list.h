#ifndef DS_LIST_H
#define DS_LIST_H

#include "hittable.h"
#include <SDL3/SDL_stdinc.h>

typedef struct{
    Hittable super;
    Hittable** list;
    Uint32 size; // actual size will be 2^this
    Uint32 inUse;
}HittableList;

HittableList* DS_CreateList();
void DS_DestroyList(HittableList* list);

void DS_ListAdd(HittableList* this, Hittable* ptr);
// no deleting

#endif