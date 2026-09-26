#include "curl/curl.h"
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "serverstate.h"
#include "info.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// THE links
// https://curl.se/libcurl/c/curl_easy_setopt.html
// https://github.com/DaveGamble/cJSON#data-structure

size_t DS_CALLBACK_Connect(char* ptr, size_t size, size_t nmemb, void* userdata){
    size_t bytes = size * nmemb;
    MasterInfo* dataprt = userdata;

    cJSON* json = cJSON_Parse(ptr);

    if(json == NULL) {
        fprintf(stderr, "Could not parse!\n");
        return bytes;
    };

    cJSON* client = cJSON_GetObjectItemCaseSensitive(json, "Client");
    cJSON* serverState = cJSON_GetObjectItemCaseSensitive(json, "ServerState");

    if(!cJSON_IsObject(client) || !cJSON_IsNumber(serverState)){
        fprintf(stderr, "Unexpected response! (%s:%d)\n",__FILE__,__LINE__);
        cJSON_Delete(json);
        return bytes;
    }

    cJSON* uuid = cJSON_GetObjectItemCaseSensitive(client,"UUID");
    cJSON* ip = cJSON_GetObjectItemCaseSensitive(client,"IP");
    cJSON* health = cJSON_GetObjectItemCaseSensitive(client,"Health");

    if(!cJSON_IsString(uuid) || !cJSON_IsString(ip) || !cJSON_IsNumber(health)){
        fprintf(stderr, "Unexpected response! (%s:%d)\n",__FILE__,__LINE__);
        cJSON_Delete(json);
        return bytes;
    }

    dataprt->client.UUID = malloc(strlen(uuid->valuestring)+1);
    strcpy(dataprt->client.UUID, uuid->valuestring);

    dataprt->client.IP = malloc(strlen(ip->valuestring)+1);
    strcpy(dataprt->client.IP, ip->valuestring);

    dataprt->client.Health = health->valueint; // this is meant to be a 64 bit number. so it will get stuck in 2038 which is like in 10 years almost lol

    dataprt->serverState = serverState->valueint;

    cJSON_Delete(json); // this does free all the other chudlings and their valuestrings too

    return bytes;
}

ServerState DS_ServerCheck(){
    return ServerWait;
};

MasterInfo DS_ServerConnect(){
    CURL* curl = curl_easy_init();
    MasterInfo data = {0};

    if(!curl){
        return data;
    };

    curl_easy_setopt(curl, CURLOPT_URL, "localhost:57165/connect");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DS_CALLBACK_Connect);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&data);

    CURLcode result = curl_easy_perform(curl);

    if(result != CURLE_OK){
        fprintf(stderr,"Could not curl!\n");
    }

    curl_easy_cleanup(curl);
    return data;
}

int main(){
    if(curl_global_init(CURL_GLOBAL_NOTHING) != CURLE_OK) return 1;
    if(DS_ServerCheck() == ServerStop){
        // I miss defer and anonymous functions well this sort of has anonymous functions but id have to split this file onto more files to not make it horrible to look at like how it already is
        curl_global_cleanup();
        return 1;
    }

    MasterInfo info = DS_ServerConnect();

    DS_DestoyMasterInfo(&info);

    curl_global_cleanup();
    return 0;
}