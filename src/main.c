#include <stdint.h>
#include <unistd.h>
#include "raylib.h"
#include "core.h"
#include "player.c"
#include "scene.c"
#include "game.c"

//TODO: Fix name convention, not sure what im doing here, it's all over the place
//TODO: Animator
//TODO: Simple Profiler
//TODO: Make Shaders Better
//TODO: load from .so
//TODO: figure out loading files independant of calling location

#define DEVTOOL

//TODO: initialize better
//Does it make sense for his to be a struct? or a memory arena for game to figure out
GameState state = {
    .debugEntityIdx = 0,
    .screenHeight =720,
    .screenWidth = 1280,
    .camera = {0},
    .lights = {0},
};

Assets GameAssets;

void ReloadCode(){
    //TODO: unload and load .so file

}

void HandleReloads(){
#ifdef DEVTOOL
    //maybe take these out of debug, and have some concept of engine flags the game uses
    if(state.debugFlags[RELOAD_SHADERS]){
        ReloadShaders(&GameAssets);
        state.debugFlags[RELOAD_SHADERS] = false;
    }

    if(state.debugFlags[RELOAD_CODE]){
        ReloadCode();
        state.debugFlags[RELOAD_CODE] = false;
    }
#endif
}


//Come back to see if this is worth looking into
//https://gafferongames.com/post/fix_your_timestep/
//TODO: draw scene only on a delta time?

void GameLoop(){
    while(!WindowShouldClose()){ 
        float dt = GetFrameTime();
        HandleInput(dt, &state);
        HandleReloads();
        UpdateAndRender(&state, &GameAssets, dt);
    }
}

void setupWindow(){
    InitWindow(state.screenWidth, state.screenHeight,"Game");
    SetTargetFPS(60);
}

int main()
{
    setupWindow();
    initScene(&state, &GameAssets);
    GameLoop();
    return 0;
}


