#ifndef __NATE_SCENE__
#define __NATE_SCENE__ 

#include "raylib.h"
#include "core.h"
#include "entity.c"
#include "camera.c"

void initPlayer(){
    entity* playerEntity = newEntity();
    playerEntity->position = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){1.0f,1.0f,1.0f};

    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;

    playerEntity->flags = playerEntity->flags | ShapeRendered;
    playerEntity->shape = Cube;
    playerEntity->color = WHITE;

    initCamera(&state.camera, playerEntity);
}


void initPlanet(Vector3 pos, Vector3 scale, float mass, Vector3 origin, float radius, float period, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = scale;
    newPlanet->mass = mass;
    newPlanet->color = color;

    orbitCircular orbit = (orbitCircular){origin, radius, period, 0.0f};
    newPlanet->orbit = orbit;

    newPlanet->flags |= Active;
    newPlanet->flags |= Orbiting;

    newPlanet->flags |= ShapeRendered;
    newPlanet->shape = Sphere;
}

void initStar(Vector3 pos, Vector3 scale, float mass, Color color){
    entity* newPlanet = newEntity();
    newPlanet->position = pos;
    newPlanet->rotation = (Vector3){0.0f,0.0f,0.0f};
    newPlanet->scale = scale;
    newPlanet->mass = mass;
    newPlanet->color = color;

    newPlanet->flags |= Active;

    newPlanet->flags |= ShapeRendered;
    newPlanet->shape = Sphere;
}


void initWorld(){
    initPlanet((Vector3){0.0f, 0.0f,0.0f}, (Vector3){1.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 50.0f, 50, BROWN);
    initPlanet((Vector3){0.0f, 0.0f,0.0f}, (Vector3){2.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 150.0f, 150, BLUE);
    initPlanet((Vector3){0.0f, 0.0f,0.0f}, (Vector3){5.0f, 1.0f,1.0f}, 1000.0f, (Vector3){0.0f, 0.0f, 0.0f}, 300.0f, 600, GREEN);
    initStar((Vector3){0.0f, 0.0f,0.0f}, (Vector3){30.0f, 1.0f,1.0f}, 1000.0f, YELLOW);
}

void initScene(){

    setDefaultData();
    initWorld();
    initPlayer();
}

#endif
