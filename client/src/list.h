#ifndef DS_LIST_H
#define DS_LIST_H

#include "hittable.h"

typedef struct HittableListRecord{
    Hittable* item;
    struct HittableListRecord* next;
    //struct HittableListRecord* previous;
} HittableListRecord;

typedef struct{
    Hittable super;
    HittableListRecord* first;
    //HittableListRecord* last;
}HittableList;

HittableList* DS_CreateList();
void DS_DestroyList(HittableList* list);

#endif