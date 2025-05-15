#pragma once

#define RLIGHTS_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "rlights.h"
#include "assetMap.h"


typedef enum{
    PAUSED,
    DRAW_DEBUG,
    SHOW_FPS,
    RELOAD_SHADERS,
    RELOAD_CODE,
    DEBUG_INDEX_COUNT
} DEBUG_INDEX;

typedef enum{
    FORWARD = KEY_W,
    BACK = KEY_S,
    LEFT = KEY_A,
    RIGHT = KEY_D,
    UP = KEY_SPACE,
    DOWN = KEY_LEFT_CONTROL,
    PAUSE = KEY_PAUSE,
    TOGGLE_DEBUG = KEY_F2,
    TOGGLE_FPS = KEY_F3,
    DEBUG_INC = KEY_KP_ADD,
    DEBUG_DEC = KEY_KP_SUBTRACT,
    RELOAD_SHADERS_KEY = KEY_F11,
    RELOAD_CODE_KEY = KEY_F10,
    CAMERA_DRAG = MOUSE_BUTTON_RIGHT, 


    
    INPUT_COUNT,
}INPUT_KEYS;



typedef enum{
    PROJECTILE,
    BEAM,
    HITSCAN,
    SPAWNER, //drones?


    WEAPON_TYPE_COUNT
}WEAPON_TYPE;


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


//TODO: union this stuff
typedef struct{
    WEAPON_TYPE type;
    float damage;
    float speed;
    int ammoCount;
    int ammoPerShot;

} weapon;



typedef struct {
    int flags;
    Vector3 position;
    Vector3 rotation;
    //Vector3 targetRotation;
    float turnSpeed;
    Vector3 scale;
    Vector3 velocity;
    union{
        int meshId;
        int modelId;
    };
    union{
        int textureId; //Not sure if I need both or not 
        int materialId;
    };
    int animFrame;
    int animIdx;
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
typedef struct Assets{
    Mesh Meshes[MESH_COUNT];
    Material Materials[MATERIAL_COUNT];
    Model Models[MODEL_COUNT];
    Texture Textures[TEXTURE_COUNT];
    Shader Shaders[SHADER_COUNT];
    ModelAnimation Animations[ANIMATION_COUNT];
} Assets;


#define MAX_ENTITIES 1024

typedef struct GameState{
    bool debugFlags[DEBUG_INDEX_COUNT];
    int debugEntityIdx; 
    int screenHeight;
    int screenWidth;

    entity entities[MAX_ENTITIES];
    Light lights[MAX_LIGHTS];
    thirdPersonCamera camera;
} GameState;

//TODO: move state to main, and actually pass it




