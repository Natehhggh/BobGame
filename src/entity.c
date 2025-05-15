#ifndef __NATE_ENTITY__
#define __NATE_ENTITY__

#include <unistd.h>
#include "core.h"


entity* newEntity(GameState * state){
    entity* newEntity = NULL;  
    for(int i = 0; i < MAX_ENTITIES; i++){
        if(state->entities[i].flags & Free){
            state->entities[i].flags = 0;
            newEntity = &state->entities[i];
            break;
        }
    }
    return newEntity;
}

void freeEntity(entity* entity){
    entity->flags = Free;
}
void setDefaultData(GameState * state){
    for(int i = 0; i < MAX_ENTITIES; ++i){
        state->entities[i].flags = Free;
    }
}




#endif
