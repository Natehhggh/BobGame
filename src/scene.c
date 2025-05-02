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
     GameAssets.Shaders[0] = LoadShader("src/lighting.vs", "src/lighting.fs");
     GameAssets.Shaders[0].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(GameAssets.Shaders[0], "viewPos");
}

void LoadModels(){
    GameAssets.Models[0] = LoadModel("./SimpleCigarShip.obj");
    GameAssets.Models[0].materials[0].shader = GameAssets.Shaders[0];
}

//conflicting rename these
void LoadMaterialsNate(){
    //TODO: test if they are copied, so I can just reuse the one
    Material matDefault = LoadMaterialDefault();
    matDefault.maps[MATERIAL_MAP_DIFFUSE].color = RED;
    GameAssets.Materials[0] = matDefault;
    Material matDefault1 = LoadMaterialDefault();
    matDefault1.maps[MATERIAL_MAP_DIFFUSE].color = YELLOW;
    GameAssets.Materials[1] = matDefault1;
    Material matDefault2 = LoadMaterialDefault();
    matDefault2.maps[MATERIAL_MAP_DIFFUSE].color = BLUE;
    GameAssets.Materials[2] = matDefault2;
}

void initPlayer(){
    entity* playerEntity = newEntity();
    playerEntity->position = (Vector3){50.0f,50.0f,50.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){1.0f,1.0f,1.0f};

    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;
    playerEntity->flags = playerEntity->flags | ModelRendered;

    playerEntity->meshId = 0;
    playerEntity->textureId = 0;

    initCamera(&state.camera, playerEntity);
}


void initPlanet(Vector3 pos, Vector3 scale, float mass, Vector3 origin, float radius, float period, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = scale;
    newPlanet->mass = mass;

    orbitCircular orbit = (orbitCircular){origin, radius, period, 0.0f};
    newPlanet->orbit = orbit;

    newPlanet->flags |= Active;
    newPlanet->flags |= Orbiting;


    //TODO, this is jank, redo it later;
    state.lights[0] = CreateLight(LIGHT_POINT, pos, Vector3Zero(), WHITE, GameAssets.Shaders[0]);


    newPlanet->meshId = 1;
    newPlanet->textureId = 2;
}

void initStar(Vector3 pos, Vector3 scale, float mass, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = scale;
    newPlanet->mass = mass;

    newPlanet->flags |= Active;

    newPlanet->meshId = 1;
    newPlanet->textureId = 1;
}


void initWorld(){
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){1.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 50.0f, 50, BROWN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){1.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 50.0f, 10, BROWN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){1.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 50.0f, 1, BROWN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){2.0f, 2.0f,2.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 150.0f, 150, BLUE);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 300.0f, 300, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 400.0f, 400, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 500.0f, 500, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 600.0f, 600, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 700.0f, 700, GREEN);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 5.0f,5.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 800.0f, 800, GREEN);
    initStar((Vector3){0.0f, 0.0f,0.0f}, (Vector3){30.0f, 30.0f,30.0f}, 1000.0f, YELLOW);
}

void initScene(){

    LoadMeshes();
    LoadTextures();
    LoadShaders();
    LoadMaterialsNate();
    LoadModels();

    setDefaultData();
    initWorld();
    initPlayer();
}

#endif
