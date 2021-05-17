#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Engine/engine_object.h"

class Camera : public EngineObject
{
public:
    Camera(Vector3 position, Vector3 rotation, Mesh mesh) : EngineObject(position, rotation, mesh) {}

    void BeforeRender()
    {
        this->rotate(Vector3(0.1, 0.1, 0.1));
    }
};

#endif