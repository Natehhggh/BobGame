#ifndef __NATE_PLAYER__
#define __NATE_PLAYER__ 

#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include <stdint.h>

//TODO: return input state, move logic to another spot
void HandleInput(float deltaTime){

    float playerSpeed = 50.0f * deltaTime; 
    Vector3 playerInputDir = {0.0f,0.0f,0.0f};

    if(IsKeyDown(KEY_W)){
        playerInputDir.x = 1.0f;
    }
    if(IsKeyDown(KEY_A)){
        playerInputDir.z = -1.0f;
    }
    if(IsKeyDown(KEY_S)){
        playerInputDir.x = -1.0f;
    }
    if(IsKeyDown(KEY_D)){
        playerInputDir.z = 1.0f;
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        playerInputDir.y = -1.0f;
    }
    if(IsKeyDown(KEY_SPACE)){
        playerInputDir.y = 1.0f;
    }

    if(IsKeyPressed(KEY_PAUSE)){
        state.paused = !state.paused;
    }

    if(IsKeyPressed(KEY_F2)){
        state.drawDebug = !state.drawDebug;
    }
    if(IsKeyPressed(KEY_F3)){
        state.showFPS = !state.showFPS;
    }

    if(IsKeyPressed(KEY_KP_ADD)){
        state.debugEntityIdx += 1;
        if(state.debugEntityIdx >= MAX_ENTITIES){
            state.debugEntityIdx = 0;
        }
    }

    if(IsKeyPressed(KEY_KP_SUBTRACT)){
        state.debugEntityIdx -= 1;
        if(state.debugEntityIdx < 0){
            state.debugEntityIdx = MAX_ENTITIES -1;
        }
    }


    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        Vector2 mouseMove = GetMouseDelta();
        state.camera.polarAngle += mouseMove.y / 100;
        state.camera.azimuthAngle += mouseMove.x / 100;
    }
    

    

    float mouseScroll = GetMouseWheelMove();
    state.camera.radius += mouseScroll;



    


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


    if(state.paused){return;}

    playerInputDir = Vector3Normalize(playerInputDir);
    playerInputDir = Vector3Scale(playerInputDir, playerSpeed);

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(state.entities[i].flags & Active && state.entities[i].flags & PlayerControlled){
            state.entities[i].position = Vector3Add(playerInputDir, state.entities[i].position);
        }
    }
    //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}


#endif
