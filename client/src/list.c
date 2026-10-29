#include "list.h"
#include "hittable.h"
#include <stdlib.h>

bool ListHit(Hittable* this, Ray* ray, float ray_tmin, float ray_tmax, HitRecord* hitRecord){
    HittableList* list = (HittableList*)this;
    HitRecord temp;
    bool hitSomething = false;
    float closest = ray_tmax;

    HittableListRecord* iteration = list->first;

    while (iteration){
        if (iteration->item->hit(iteration->item,ray,ray_tmin,closest,&temp)){
            hitSomething = true;
            closest = temp.t;
            *hitRecord = temp;
        };
        iteration = iteration->next;
    }
    return hitSomething;
}

HittableList* DS_CreateList(){
    HittableList* list = calloc(1, sizeof(HittableList));
    list->super.hit = &ListHit;
    return list;
};

void DS_DestroyList(HittableList* list){
    free(list);
};