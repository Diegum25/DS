#ifndef DS_INFO_H
#define DS_INFO_H

#include <SDL3/SDL_stdinc.h>
#include "serverstate.h"

typedef struct{
    char* UUID;
    char* IP;
    Uint64 Health;
}ClientInfo;

typedef struct{
    ClientInfo client;
    ServerState serverState;
}MasterInfo;

void DS_DestoyMasterInfo(MasterInfo* info);

#endif