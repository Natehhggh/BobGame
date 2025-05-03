#ifndef __NATE_SCENE__
#define __NATE_SCENE__ 

#include "raylib.h"
#include "core.h"
#include "entity.c"
#include "camera.c"
#include <raymath.h>


void LoadMeshes(){
    GameAssets.Meshes[0] = GenMeshCube(1,1,1);
    GameAssets.Meshes[1] = GenMeshSphere(1,32,32); //test other values
    //GameAssets.Meshes[2] = GenMeshCylinder();
    //GameAssets.Meshes[3] = GenMeshCapsule();
    //GameAssets.Meshes[4] = GenMeshPlane();
}


//TODO: Texture atlas? not sure if you can in this case?
//upload texture look into, guess that does something for rendering a mesh
void LoadTextures(){
    //GameAssets.Textures[0] = LoadTextureFromImage(GenImageColor(1, 1, RED));
    //GameAssets.Textures[1] = LoadTextureFromImage(GenImageColor(1, 1, YELLOW));
    //GameAssets.Textures[2] = LoadTextureFromImage(GenImageColor(1, 1, BLUE));

}


void LoadShaders(){
     GameAssets.Shaders[0] = LoadShader("src/shaders/lighting.vert.glsl", "src/shaders/lighting.frag.glsl");
     GameAssets.Shaders[0].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(GameAssets.Shaders[0], "viewPos");
     GameAssets.Shaders[1] = LoadShader("src/shaders/sun.vert.glsl", "src/shaders/sun.frag.glsl");
     GameAssets.Shaders[1].locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(GameAssets.Shaders[1], "emission");
     GameAssets.Shaders[1].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(GameAssets.Shaders[1], "viewPos");

}

void AssignShaders(){
    GameAssets.Models[0].materials[0].shader = GameAssets.Shaders[0];
    GameAssets.Materials[2].shader = GameAssets.Shaders[0];
    GameAssets.Materials[1].shader = GameAssets.Shaders[1];
}


void ReloadShaders(){
    UnloadShader(GameAssets.Shaders[0]);
    UnloadShader(GameAssets.Shaders[1]);
    LoadShaders();
    AssignShaders();

}

void LoadModels(){
    GameAssets.Models[0] = LoadModel("./SimpleCigarShip.obj");
}

//conflicting rename these
void LoadMaterialsNate(){
    //TODO: test if they are copied, so I can just reuse the one
    Material matDefault = LoadMaterialDefault();
    matDefault.maps[MATERIAL_MAP_DIFFUSE].color = RED;
    GameAssets.Materials[0] = matDefault;
    Material matDefault1 = LoadMaterialDefault();
    matDefault1.maps[MATERIAL_MAP_DIFFUSE].color = YELLOW;
    matDefault1.maps[MATERIAL_MAP_EMISSION].color = WHITE;
    matDefault1.maps[MATERIAL_MAP_EMISSION].value = 1.0f;
    matDefault1.maps[MATERIAL_MAP_EMISSION].texture = LoadTextureFromImage(GenImageColor(1, 1, WHITE));


    GameAssets.Materials[1] = matDefault1;
    Material matDefault2 = LoadMaterialDefault();
    matDefault2.maps[MATERIAL_MAP_DIFFUSE].color = BLUE;
    GameAssets.Materials[2] = matDefault2;
}

void initPlayer(){
    entity* playerEntity = newEntity();
    playerEntity->position = (Vector3){1000.0f,0.0f,0.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){1.0f,1.0f,1.0f};

    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;
    playerEntity->flags = playerEntity->flags | ModelRendered;

    playerEntity->meshId = 0;
    playerEntity->textureId = 0;

    initCamera(&state.camera, playerEntity);
}


void initPlanet(Vector3 pos, float scale, float mass, Vector3 origin, float radius, float period, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = (Vector3){scale, scale, scale};
    newPlanet->mass = mass;

    orbitCircular orbit = (orbitCircular){origin, radius, period, 0.0f};
    newPlanet->orbit = orbit;

    newPlanet->flags |= Active;
    newPlanet->flags |= Orbiting;
    newPlanet->tint = color;

    newPlanet->meshId = 1;
    newPlanet->textureId = 2;
}

void initStar(Vector3 pos, float scale, float mass, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = (Vector3){scale, scale, scale};
    newPlanet->mass = mass;

    newPlanet->flags |= Active;
    newPlanet->tint = color;

    state.lights[0] = CreateLight(LIGHT_POINT, pos, Vector3Zero(), BLUE, GameAssets.Shaders[0]);
    newPlanet->meshId = 1;
    newPlanet->textureId = 1;
}


//TODO: store this in some format and read into it
void initWorld(){
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 10.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 500.0f, 50, DARKBROWN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 12.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 1500.0f, 150, BROWN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 40.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 3000.0f, 300, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 30.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 4000.0f, 400, RED);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 100.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 6000.0f, 600, BEIGE);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 70.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 7000.0f, 700, BLUE);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 5.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 8000.0f, 800, DARKGRAY);
    initStar((Vector3){0.0f, 0.0f,0.0f}, 300.0f, 1000.0f, YELLOW);
}

void initScene(){
    //TODO: Load these seperately
    LoadMeshes();
    LoadTextures();
    LoadShaders();
    LoadMaterialsNate();
    LoadModels();
    AssignShaders();

    setDefaultData();
    initWorld();
    initPlayer();
}

#endif
