#ifndef __NATE_PLAYER__
#define __NATE_PLAYER__ 

#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include <stdint.h>
//TODO: return input state, move logic to another spot
void HandleInput(float deltaTime, GameState *state){

    //TODO: Move variables to game objects
    float playerSpeed = 500.0f * deltaTime; 
    float scaleChange = 1.0f;
    Vector3 playerInputDir = {0.0f,0.0f,0.0f};

    if(IsKeyDown(FORWARD)){
        playerInputDir.x = 1.0f;
    }
    if(IsKeyDown(LEFT)){
        playerInputDir.z = -1.0f;
    }
    if(IsKeyDown(BACK)){
        playerInputDir.x = -1.0f;
    }
    if(IsKeyDown(RIGHT)){
        playerInputDir.z = 1.0f;
    }
    if(IsKeyDown(DOWN)){
        playerInputDir.y = -1.0f;
    }
    if(IsKeyDown(UP)){
        playerInputDir.y = 1.0f;
    }

    if(IsKeyDown(KEY_PAGE_UP)){
        scaleChange = 1.0f + (0.1f * deltaTime);
    }
    if(IsKeyDown(KEY_PAGE_DOWN)){
        scaleChange = 1.0f - (0.1f * deltaTime);
    }

    if(IsKeyPressed(PAUSE)){
        state->debugFlags[PAUSED] = !state->debugFlags[PAUSED];
    }

    if(IsKeyPressed(TOGGLE_DEBUG)){
        state->debugFlags[DRAW_DEBUG] = !state->debugFlags[DRAW_DEBUG];
    }
    if(IsKeyPressed(TOGGLE_FPS)){
        state->debugFlags[SHOW_FPS] = !state->debugFlags[SHOW_FPS];
    }

    if(IsKeyPressed(DEBUG_INC)){
        state->debugEntityIdx += 1;
        if(state->debugEntityIdx >= MAX_ENTITIES){
            state->debugEntityIdx = 0;
        }
    }

    if(IsKeyPressed(DEBUG_DEC)){
        state->debugEntityIdx -= 1;
        if(state->debugEntityIdx < 0){
            state->debugEntityIdx = MAX_ENTITIES -1;
        }
    }

    if(IsKeyPressed(RELOAD_SHADERS_KEY)){
        state->debugFlags[RELOAD_SHADERS] = true;
    }

    if(IsKeyPressed(RELOAD_CODE_KEY)){
        state->debugFlags[RELOAD_CODE] = true;
    }

    if(IsMouseButtonDown(CAMERA_DRAG)){
        Vector2 mouseMove = GetMouseDelta();
        state->camera.polarAngle += mouseMove.y / 100;
        state->camera.azimuthAngle += mouseMove.x / 100;
    }
    

    
    //TODO: put caps on, and some easing function to make scrolling feel bettr
    float mouseScroll = GetMouseWheelMove();
    state->camera.radius += mouseScroll * 1.5f;



    

    //TODO: move to settings
    if(IsKeyPressed(KEY_KP_0)){
        SetTargetFPS(10000000);
    }
    if(IsKeyPressed(KEY_KP_1)){
        SetTargetFPS(15);
    }
    if(IsKeyPressed(KEY_KP_2)){
        SetTargetFPS(30);
    }
    if(IsKeyPressed(KEY_KP_3)){
        SetTargetFPS(60);
    }
    if(IsKeyPressed(KEY_KP_4)){
        SetTargetFPS(120);
    }


    if(state->debugFlags[PAUSED]){return;}

    playerInputDir = Vector3Normalize(playerInputDir);
    playerInputDir = Vector3Scale(playerInputDir, playerSpeed);

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(state->entities[i].flags & Active && state->entities[i].flags & PlayerControlled){
            state->entities[i].position = Vector3Add(playerInputDir, state->entities[i].position);
            state->entities[i].velocity = playerInputDir;
            state->entities[i].scale = Vector3Scale(state->entities[i].scale, scaleChange);
        }
    }
    //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}


#endif
