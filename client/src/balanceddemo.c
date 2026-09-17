#include "camera.h"
#include "hittable.h"
#include "image.h"
#include "rayutil.h"
#include "sphere.h"
#include <stdlib.h>
#include "cglm/vec3.h"
#include "stdio.h"

#include <SDL3/SDL_stdinc.h>
#include "SDL3/SDL_thread.h"
#include "SDL3/SDL_mutex.h"

SDL_Mutex* dataMutex;

typedef struct{
    Uint32 rayCount;
    Ray* p_Rays;
    Uint32 nextRay;
    Image* p_Image;
    Hittable* p_Hittable;
}BounceData;

int Bounce(void * p_Data){
    BounceData* data = p_Data;

    while(true){
        SDL_LockMutex(dataMutex);

        if(data->nextRay >= data->rayCount){
            SDL_UnlockMutex(dataMutex);
            return 0;
        }

        Uint32 myRay = data->nextRay++;

        SDL_UnlockMutex(dataMutex);

        // i dont believe this could cause a problem

        Pixel color = DS_RayColor(&data->p_Rays[myRay],data->p_Hittable);

        data->p_Image->image[myRay] = color;

    }

    return 666;
}

void MultiThread(Uint16 threadCount, Image* p_Image, Camera* p_Camera, Hittable* p_Hittable){
    Uint32 rayCount = p_Image->width*p_Image->height;
    Ray* rays = calloc(rayCount, sizeof(Ray));
    for(int i = 0; i < p_Image->width;i++){
        for(int j = 0; j < p_Image->height; j++){
            vec3 horizontal = {0}; glm_vec3_scale(p_Camera->viewport.horizontalDelta, i, horizontal);
            vec3 vertical = {0}; glm_vec3_scale(p_Camera->viewport.verticalDelta, j, vertical);

            vec3 pixel = {0};
            glm_vec3_add(p_Camera->zero, horizontal, pixel);
            glm_vec3_add(pixel, vertical, pixel);

            vec3 direction = {0};
            glm_vec3_sub(pixel, p_Camera->position, direction);

            Ray ray = {0};
            glm_vec3_copy(p_Camera->position, ray.origin);
            glm_vec3_copy(direction, ray.destination);
            rays[i+(j * p_Image->width)] = ray;
        }
    }

    SDL_Thread** threads = calloc(threadCount,sizeof(void*));

    dataMutex = SDL_CreateMutex();

    BounceData data = {.p_Hittable = p_Hittable, .p_Image = p_Image, .p_Rays = rays, .rayCount = rayCount, .nextRay = 0};

    for(int i = 0; i < threadCount; i++){
        threads[i] = SDL_CreateThread(Bounce,"Thread",&data);
    }

    for(int i = 0; i < threadCount; i++){
        int status = -1;
        SDL_WaitThread(threads[i], &status);
        if(status != 0){
            printf("thread %p returned %d\n",threads[i],status);
        }
    }

    free(threads);
    free(rays);
}

int main(){

    Uint16 x = 800, y = 800;
    
    Image* image = DS_CreateImage(x,y);

    Camera cam = DS_CreateCamera(image);

    vec3 pos = {0,0,-2};
    Sphere* sphere = DS_CreateSphere(pos,0.5f);

    Hittable* trolololo = (Hittable*)sphere;

    MultiThread(4, image, &cam, trolololo);

    DS_WriteImage(image, "build/rays.png");

    DS_DestroySphere(sphere);

    DS_DestroyImage(image);

    return 0;
};