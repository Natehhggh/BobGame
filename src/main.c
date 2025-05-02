#include <math.h>
#include <stdint.h>
#include <unistd.h>
//#include "rlights.h"
#include "raylib.h"
#include "core.h"
#include "camera.c"
#include "player.c"
#include "scene.c"

//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"


//TODO: Fix name convention, not sure what im doing here, it's all over the place
//TODO: Check Flags Raylib, named vsync
//TODO: Animator
//TODO: Simple Profiler
//TODO: Make Shaders Better
//TODO: load from .so

void setup(){
    InitWindow(state.screenWidth, state.screenHeight,"Jam Game");
    SetTargetFPS(60);
    initScene();
}




//TODO: can I store the matrixes instead of creating them?
void drawMeshes(){
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if(state.entities[i].flags & Active && !(state.entities[i].flags & ModelRendered)){
            Vector3 scale = state.entities[i].scale;
            Vector3 rotationAxis = state.entities[i].rotation;
            Vector3 position = state.entities[i].position;
            float rotationAngle = 0.0f;
            Matrix matScale = MatrixScale(scale.x, scale.y, scale.z);
            Matrix matRotation = MatrixRotate(rotationAxis, rotationAngle);
            Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);
            Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
            DrawMesh(GameAssets.Meshes[state.entities[i].meshId] , GameAssets.Materials[state.entities[i].textureId] , matTransform);
        }else if(state.entities[i].flags & Active && ModelRendered){
            //BeginShaderMode(GameAssets.Shaders[0]);
            DrawModelEx(GameAssets.Models[state.entities[i].meshId], state.entities[i].position, state.entities[i].rotation, 0.0f, state.entities[i].scale, WHITE);
            //EndShaderMode();
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
            drawMeshes();
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
        float cameraPos[3] = {state.camera.camera.position.x, state.camera.camera.position.y, state.camera.camera.position.z};
        SetShaderValue(GameAssets.Shaders[0], GameAssets.Shaders[0].locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        UpdateLightValues(GameAssets.Shaders[0], state.lights[0]);
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


