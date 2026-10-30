#include "list.h"
#include "hittable.h"
#include <stdlib.h>

bool ListHit(Hittable* this, Ray* ray, float ray_tmin, float ray_tmax, HitRecord* hitRecord){
    HittableList* list = (HittableList*)this;
    HitRecord temp;
    bool hitSomething = false;
    float closest = ray_tmax;

    for(int i = 0; i < list->inUse; i++){
        Hittable* hittable = list->list[i];
        if (hittable->hit(hittable,ray,ray_tmin,closest,&temp)){
            hitSomething = true;
            closest = temp.t;
            *hitRecord = temp;
        };
    }
    return hitSomething;
}

int ipow(int x, int y){
    if(y == 0) return 1;

    int result = x;
    for (int i = 0; i < y; i++){
        result *= result;
    }
    return result;
};

HittableList* DS_CreateList(){
    HittableList* list = calloc(1, sizeof(HittableList));
    list->super.hit = &ListHit;
    list->list = calloc(ipow(2, list->size),sizeof(void*));
    return list;
};

void DS_ListAdd(HittableList* this, Hittable* ptr){
    if(this->inUse >= ipow(2, this->size)){
        this->size++;
        this->list = realloc(this->list, ipow(2, this->size));
    }
    this->list[this->inUse++] = ptr;
};

void DS_DestroyList(HittableList* list){
    free(list->list);
    free(list);
};