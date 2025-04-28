#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include "raylib.h"
#include "core.h"
#include "camera.c"
#include "rlights.h"
#include "player.c"
#include "scene.c"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps flag ~8kfps

//TODO: Fix name convention, not sure what im doing here, it's all over the place
//TODO: Add Screenshot system
//TODO: Check Flags Raylib, named vsync
//TODO: Load Real Model and animate
//TODO: Simple Profiler

void setup(){
    InitWindow(state.screenWidth, state.screenHeight,"Jam Game");
    SetTargetFPS(60);
    initScene();
}


//TODO: move to some rendering file, dont want to look at rendering logic here
void drawPrimativeShapes(){
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if(state.entities[i].flags & Active && state.entities[i].flags & ShapeRendered){
            switch(state.entities[i].shape){
                case Cube:
                    DrawCubeV(state.entities[i].position, state.entities[i].scale, state.entities[i].color);
                    break;
                case Sphere:
                    DrawSphere(state.entities[i].position, state.entities[i].scale.x, state.entities[i].color);
                    break;
                case Cylinder:
                    DrawCubeV(state.entities[i].position, state.entities[i].scale, state.entities[i].color);
                    break;
                case Capsule:
                    DrawCubeV(state.entities[i].position, state.entities[i].scale, state.entities[i].color);
                    break;
                case Plane:
                    DrawPlane(state.entities[i].position,
                            (Vector2){state.entities[i].scale.x, state.entities[i].scale.z}, state.entities[i].color);
                    break;
            }
        }
    }
}


void drawUI(){
    


    if(state.drawDebug){
        entity *debugEntity = &state.entities[state.debugEntityIdx];
        DrawText(TextFormat("debugId: %d", state.debugEntityIdx), 800, 40, 12, RED);
        DrawText(TextFormat("Target x: %02.02f y: %02.02f z: %02.02f", debugEntity->position.x, debugEntity->position.y, debugEntity->position.z), 800, 50, 12, RED);
    }
    if(state.showFPS){
        DrawFPS(10,10);
        DrawText(TextFormat("Frame time: %02.04f ms", GetFrameTime()* 1000), 10, 30, 20, GREEN);
    }


}

void DrawScene(){
    BeginDrawing();
    {
        ClearBackground(BLACK);
        
        BeginMode3D(state.camera.camera);
        {
            //TODO: Render struct 
            drawPrimativeShapes();
        }
        EndMode3D();

        drawUI();



    }
    EndDrawing();
}


void UpdateOrbits(float dt){
    if(state.paused){return;}
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if((state.entities[i].flags & Active) && (state.entities[i].flags & Orbiting)){
            state.entities[i].orbit.t += dt;
            float x = state.entities[i].orbit.t / state.entities[i].orbit.period * 2.0f * 3.14159f;
            if(state.entities[i].orbit.t >= state.entities[i].orbit.period){
                state.entities[i].orbit.t -= state.entities[i].orbit.period;
            }
            state.entities[i].position.x = sin(x) * state.entities[i].orbit.radius;
            state.entities[i].position.z = cos(x) * state.entities[i].orbit.radius;
            //Vector3 pos = getOrbitPos(entities[i].orbit);
            //entities[i].position = pos;
        }
    }
}


//TODO: draw scene only on a delta time?
void GameLoop(){
    while(!WindowShouldClose()){ 
        float dt = GetFrameTime();
        HandleInput(dt);
        UpdateOrbits(dt);
        updateCamera(&state.camera);
        DrawScene();
    }
}
//TODO: Do this
//come back to it, going to pass dt into updates and use that for now
//https://gafferongames.com/post/fix_your_timestep/
void GameLoop2(){
    //clock_t clockOld, timeNew;
     
    //double timeOld = time(NULL);
    double t = 0.0f;
    double dt = 0.01f;
    double accumulator = 0.0f;
    while(!WindowShouldClose())
    {

        //double timeNew = time(NULL);
        //double timeSince = timeNew - timeOld;
        //timeOld = timeNew;
        //if(timeSince > 0.25){
         //   timeSince = 0.25;
        //}
        //HandleInput();
        //updateSprites();
        //updateCamera(&camera);
        //DrawScene();
    }

}

int main()
{
    setup();
    GameLoop();
    return 0;
}


