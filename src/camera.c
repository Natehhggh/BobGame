#ifndef __NATE_CAMERA__
#define __NATE_CAMERA__

#include "raylib.h"
#include "core.h"
#include <math.h>
#include <raymath.h>


void updateCamera(thirdPersonCamera* camera){
    //Vector3 IdealOffset = >

    Vector3 targetPos = camera->target->position;
    //camera->camera.position = Vector3Add(targetPos, camera->offset);
    float r = camera->radius;
    float theta = camera->polarAngle;
    float phi = camera->azimuthAngle;
    camera->camera.position = Vector3Add(targetPos, (Vector3){r * sin(theta) * cos(phi), r* cos(theta),  r * sin(theta) * sin(phi) });
    camera->camera.target = targetPos;
}

void initCamera(thirdPersonCamera* camera, entity* target){
    //camera->camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera->radius = 5.0f;
    camera->polarAngle = 1.57f; //roughly pi/2
    camera->azimuthAngle = 1.57f;
    camera->camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera->camera.fovy = 90.0f;
    camera->camera.projection = CAMERA_PERSPECTIVE;
    camera->target = target;
    //camera->offset = Vector3Subtract(camera->camera.position, target->position);
}


#endif

