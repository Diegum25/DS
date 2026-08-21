#include "curl/curl.h"
#include <curl/easy.h>
#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int main(){
    CURL* curl = curl_easy_init();

    if(!curl) return 1;

    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/yoyoyoyo");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    CURLcode code = curl_easy_perform(curl);
    if(code != CURLE_OK) return 1;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata){
    const size_t bytes = size * nmemb;

    for (unsigned int i = 0; i < bytes; i++){
        printf("%c",ptr[i]);
    }

    return bytes;
}