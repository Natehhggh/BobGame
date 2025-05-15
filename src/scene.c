#pragma  once

#include "assetMap.h"
#include "raylib.h"
#include "core.h"
#include "entity.c"
#include "camera.c"
#include <raymath.h>


void LoadMeshes(Assets *assets){
    assets->Meshes[CUBE] = GenMeshCube(1,1,1);
    assets->Meshes[SPHERE] = GenMeshSphere(1,32,32); //test other values
    //GameAssets.Meshes[2] = GenMeshCylinder();
    //GameAssets.Meshes[3] = GenMeshCapsule();
    //GameAssets.Meshes[4] = GenMeshPlane();
}


//TODO: Texture atlas? not sure if you can in this case?
//upload texture look into, guess that does something for rendering a mesh
void LoadTextures(Assets *assets){
    //GameAssets.Textures[0] = LoadTextureFromImage(GenImageColor(1, 1, RED));
    //GameAssets.Textures[1] = LoadTextureFromImage(GenImageColor(1, 1, YELLOW));
    //GameAssets.Textures[2] = LoadTextureFromImage(GenImageColor(1, 1, BLUE));

}


void LoadShaders(Assets *assets){
     assets->Shaders[LIGHTING_SHADER] = LoadShader("src/shaders/lighting.vert.glsl", "src/shaders/lighting.frag.glsl");
     assets->Shaders[LIGHTING_SHADER].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(assets->Shaders[LIGHTING_SHADER], "viewPos");
     assets->Shaders[SUN_SHADER] = LoadShader("src/shaders/sun.vert.glsl", "src/shaders/sun.frag.glsl");
     assets->Shaders[SUN_SHADER].locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(assets->Shaders[SUN_SHADER], "emission");
     assets->Shaders[SUN_SHADER].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(assets->Shaders[SUN_SHADER], "viewPos");

}

void AssignShaders(Assets *assets){
    //assign lighting shader to all model materials
    for(int i = 0; i < MODEL_COUNT; i++){
        for(int j = 0; j < assets->Models[i].materialCount; j++){
            assets->Models[i].materials[j].shader = assets->Shaders[LIGHTING_SHADER];
        }
    }

    assets->Materials[PLANET_MAT].shader = assets->Shaders[LIGHTING_SHADER];
    assets->Materials[SUN_MAT].shader = assets->Shaders[SUN_SHADER];
}


void ReloadShaders(Assets *assets){
    UnloadShader(assets->Shaders[0]);
    UnloadShader(assets->Shaders[1]);
    LoadShaders(assets);
    AssignShaders(assets);

}


void LoadModels(Assets *assets){
    assets->Models[CIGAR_SHIP] = LoadModel("./assets/SimpleCigarShip.obj");
    assets->Models[REDSHIP] = LoadModel("./assets/RedShip.glb");
    assets->Models[GIRL] = LoadModel("./assets/girl.glb");
    int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations("./assets/girl.glb", &animsCount);
    assets->Animations[TEST_WALK] = anims[0];
}

//conflicting rename these
void LoadMaterialsNate(Assets *assets){
    //TODO: test if they are copied, so I can just reuse the one
    assets->Materials[PLANET_MAT] = LoadMaterialDefault();
    assets->Materials[SUN_MAT] = LoadMaterialDefault();
    assets->Materials[SUN_MAT].maps[MATERIAL_MAP_DIFFUSE].color = YELLOW;
    assets->Materials[SUN_MAT].maps[MATERIAL_MAP_EMISSION].color = WHITE;
    assets->Materials[SUN_MAT].maps[MATERIAL_MAP_EMISSION].value = 1.0f;
    assets->Materials[SUN_MAT].maps[MATERIAL_MAP_EMISSION].texture = LoadTextureFromImage(GenImageColor(1, 1, WHITE));
}

void initPlayer(GameState * state){
    entity* playerEntity = newEntity(state);
    playerEntity->position = (Vector3){1000.0f,0.0f,0.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){1.0f,1.0f,1.0f};

    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;
    playerEntity->flags = playerEntity->flags | ModelRendered;

    playerEntity->modelId = 1;
    playerEntity->materialId = 0;
    playerEntity->turnSpeed = 30.0f;

    initCamera(&state->camera, playerEntity);
}


void initPlanet(Vector3 pos, float scale, float mass, Vector3 origin, float radius, float period, Color color, GameState *state){
    entity* newPlanet = newEntity(state);
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = (Vector3){scale, scale, scale};
    newPlanet->mass = mass;

    orbitCircular orbit = (orbitCircular){origin, radius, period, 0.0f};
    newPlanet->orbit = orbit;

    newPlanet->flags |= Active;
    newPlanet->flags |= Orbiting;
    newPlanet->tint = color;

    newPlanet->meshId = SPHERE;
    newPlanet->materialId = PLANET_MAT;
}

void initStar(Vector3 pos, float scale, float mass, Color color, GameState *state, Assets * gameAssets){
    entity* newPlanet = newEntity(state);
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = (Vector3){scale, scale, scale};
    newPlanet->mass = mass;

    newPlanet->flags |= Active;
    newPlanet->tint = color;

    //TODO: connect light to lifetime of emitter so I can update
    state->lights[0] = CreateLight(LIGHT_POINT, pos, Vector3Zero(), WHITE, gameAssets->Shaders[LIGHTING_SHADER]);
    newPlanet->meshId = SPHERE;
    newPlanet->materialId = SUN_MAT;
}


//TODO: store this in some format and read into it
void initWorld(GameState * state, Assets * assets){
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 10.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 500.0f, 50, DARKBROWN, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 12.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 1500.0f, 150, BROWN, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 40.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 3000.0f, 300, GREEN, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 30.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 4000.0f, 400, RED, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 100.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 6000.0f, 600, BEIGE, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 70.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 7000.0f, 700, BLUE, state);
    initPlanet((Vector3){0.0f, 0.0f, 0.0f}, 5.0f, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 8000.0f, 800, DARKGRAY, state);
    initStar((Vector3){0.0f, 0.0f,0.0f}, 300.0f, 1000.0f, YELLOW, state, assets);
}

void initScene(GameState *state, Assets *gameAssets){
    //TODO: Load these seperately
    LoadMeshes(gameAssets);
    LoadTextures(gameAssets);
    LoadShaders(gameAssets);
    LoadMaterialsNate(gameAssets);
    LoadModels(gameAssets);
    AssignShaders(gameAssets);

    setDefaultData(state);
    initWorld(state, gameAssets);
    initPlayer(state);
}

