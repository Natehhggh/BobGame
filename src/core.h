#ifndef __NATE_CORE__
#define __NATE_CORE__

#define RLIGHTS_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "rlights.h"

#define WORLD_HEIGHT = 20;
#define WORLD_WIDTH = 20;


typedef enum {
    Free = 1 << 0,
    Active = 1 << 1,
    PlayerControlled = 1 << 2,
    Orbiting = 1 << 3,
    ModelRendered = 1 << 4,
    Unused002 = 1 << 5,
    Unused003 = 1 << 6,
    Unused004 = 1 << 7,
    Unused005 = 1 << 8,
    Unused006 = 1 << 9,
    Unused007 = 1 << 10,
    Unused008 = 1 << 11,
    Unused009 = 1 << 12,
    Unused010 = 1 << 13,
    Unused011 = 1 << 14,
    Unused012 = 1 << 15,
    Unused013 = 1 << 16,
    Unused014 = 1 << 17,
    Unused015 = 1 << 18,
    Unused016 = 1 << 19,
    Unused017 = 1 << 20,
    Unused018 = 1 << 21,
    Unused019 = 1 << 22,
    Unused020 = 1 << 23,
    Unused021 = 1 << 24,
    Unused022 = 1 << 25,
    Unused023 = 1 << 26,
    Unused024 = 1 << 27,
    Unused025 = 1 << 28,
    Unused026 = 1 << 29,
} entityFlags;

typedef struct {
    Vector3 origin;
    float radius;
    float period;
    float t; //TODO: make a universal time so everything doesn't reset
} orbitCircular;

//https://en.wikipedia.org/wiki/Kepler_orbit
//We can have cool orbits when the idea works
typedef struct {
    Vector3 origin;
    float a; //semi major axis
    float e; //eccentricity
    float period;
    float t; 
} orbit;

typedef struct {
    int flags;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Vector3 velocity;
    int meshId;
    int textureId;
    float mass;
    Color tint;
    orbitCircular orbit;
} entity;


//TODO: enum for other cameras like first person, just get any camera in here
typedef struct thirdPersonCamera{
    entity* target;
    Camera3D camera;
    Vector3 offset;
    float radius;
    float polarAngle;
    float azimuthAngle;

} thirdPersonCamera;


//TODO: look into models, seems like thats how they get animated in raylib, not sure if it's right
//Can I instance render a model playing random animation frames or only meshes are instanced? do I care about instance rendering for the scale of any game I make?
// TODO: enums for indexes, so I can auto increment count as needed
typedef struct Assets{
    Mesh Meshes[16];
    Material Materials[16];
    Model Models[16];
    Texture Textures[16];
    Shader Shaders[16];

} Assets;


#define MAX_ENTITIES 1024

typedef struct GameState{
    bool paused;
    bool drawDebug;
    bool showFPS;
    bool reloadShaders;
    bool reloadCode; //TODO: Hot Reload
    int debugEntityIdx; 
    int screenHeight;
    int screenWidth;

    entity entities[MAX_ENTITIES];
    Light lights[MAX_LIGHTS];
    thirdPersonCamera camera;
} GameState;

//TODO: move state to main, and actually pass it

GameState state = {
    .debugEntityIdx = 0,
    .screenHeight =720,
    .screenWidth = 1280,
    .camera = {0},
    .lights = {0},
};

Assets GameAssets;



#endif
