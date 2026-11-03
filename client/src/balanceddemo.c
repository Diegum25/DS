#include "list.h"
#include "ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
    Ray** p_Rays;
    Uint32 nextSet;
    Image* p_Image;
    Hittable* p_Hittable;
    Uint16 samples;
}BounceData;

int Bounce(void * p_Data){
    BounceData* data = p_Data;

    while(true){
        SDL_LockMutex(dataMutex);

        if(data->nextSet >= data->p_Image->height * data->p_Image->width){
            SDL_UnlockMutex(dataMutex);
            return 0;
        }

        Uint32 mySet = data->nextSet++;

        SDL_UnlockMutex(dataMutex); // i dont believe this could cause a problem

        Uint32 r = 0, g = 0, b = 0; // averages

        for(int i = 0; i < data->samples; i++){
            Pixel color = DS_RayColor(&data->p_Rays[mySet][i],data->p_Hittable);
            r += color.r;
            g += color.g;
            b += color.b;
        }

        r = r / data->samples;
        g = g / data->samples;
        b = b / data->samples;

        Pixel final = {.r = r, .g = g, .b = b, .a = 255};

        data->p_Image->image[mySet] = final;
    }

    return 666;
}

void RandomizeRayABit(Ray* ray){
    vec3 axis1 = {1,0,0};
    vec3 axis2 = {0,1,0};
    glm_vec3_rotate(ray->destination, (SDL_randf()*2 -1)/1024, axis1); // this looks alr8
    glm_vec3_rotate(ray->destination, (SDL_randf()*2 -1)/1024, axis2);
};

void SampleRandomThing(vec3 dest){
    vec3 thing = {SDL_randf() - 0.5f, SDL_randf() - 0.5f, 0.0f};
    glm_vec3_copy(thing, dest);
};

void MultiThread(Uint16 threadCount, Uint16 samples, Image* p_Image, Camera* p_Camera, Hittable* p_Hittable){
    Ray** imagePixelRays = calloc(p_Image->width*p_Image->height, sizeof(void*));
    for(int i = 0; i < p_Image->width;i++){
        for(int j = 0; j < p_Image->height; j++){
            imagePixelRays[i+(j * p_Image->width)] = calloc(samples, sizeof(Ray));
            for(int k = 0; k < samples; k++){
                vec3 offset = {0}; SampleRandomThing(offset);
                vec3 horizontal = {0}; glm_vec3_scale(p_Camera->viewport.horizontalDelta, i + offset[0], horizontal);
                vec3 vertical = {0}; glm_vec3_scale(p_Camera->viewport.verticalDelta, j + offset[1], vertical);

                vec3 pixel = {0};
                glm_vec3_add(p_Camera->zero, horizontal, pixel);
                glm_vec3_add(pixel, vertical, pixel);

                vec3 direction = {0};
                glm_vec3_sub(pixel, p_Camera->position, direction);
                Ray ray = {0};
                glm_vec3_copy(p_Camera->position, ray.origin);
                glm_vec3_copy(direction, ray.destination);
                imagePixelRays[i+(j * p_Image->width)][k] = ray; // i have no idea why theyre arranged like that anymore lol
            }
        }
    }

    SDL_Thread** threads = calloc(threadCount,sizeof(void*));

    dataMutex = SDL_CreateMutex();

    BounceData data = {.p_Hittable = p_Hittable, .p_Image = p_Image, .p_Rays = imagePixelRays, .nextSet = 0, .samples = samples};

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
    for(int i = 0; i < p_Image->width*p_Image->height; i++){
        free(imagePixelRays[i]);
    }
    free(imagePixelRays);
}

int main(){

    Uint16 x = 800, y = 800;

    Uint16 samples = 16;
    
    Image* image = DS_CreateImage(x,y);

    Camera cam = DS_CreateCamera(image);

    HittableList* list = DS_CreateList();

    vec3 pos1 = {0,0,-2};
    Sphere* sphere = DS_CreateSphere(pos1, 0.5f);

    vec3 pos2 = {0,-5.5f,-2};
    Sphere* sphere2 = DS_CreateSphere(pos2, 5.0f);

    DS_ListAdd(list, (Hittable*)sphere);
    DS_ListAdd(list, (Hittable*)sphere2);

    const int randomBalls = 10;
    Sphere* bolas[randomBalls];

    for (int i = 0; i < randomBalls; i++){
        vec3 pos = {SDL_randf()*5 - 2.5f,SDL_randf()*5,-SDL_randf()*5};
        bolas[i] = DS_CreateSphere(pos, SDL_randf());
        DS_ListAdd(list, (Hittable *)bolas[i]);
    };

    MultiThread(4, samples, image, &cam, (Hittable*)list);

    DS_WriteImage(image, "build/rays.png"); // <- wont say anything if there is no build dir lol.

    DS_DestroyList(list);

    DS_DestroySphere(sphere);
    DS_DestroySphere(sphere2);

    for (int i = 0; i < randomBalls; i++){
        DS_DestroySphere(bolas[i]);
    };

    DS_DestroyImage(image);

    return 0;
};