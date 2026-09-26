#include "info.h"
#include <stdlib.h>

void DS_DestoyMasterInfo(MasterInfo *info){
    free(info->client.UUID);
    free(info->client.IP);
}