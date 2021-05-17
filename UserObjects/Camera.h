#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Engine/engine_object.h"
#include "Engine/input.h"

class Camera : public EngineObject
{
public:
    Camera(Vector3 position, Vector3 rotation, Mesh mesh) : EngineObject(position, rotation, mesh) {}

    void BeforeRender()
    {
        this->translate(Vector3(
            0.1 * (Input::is_key_pressed('d') - Input::is_key_pressed('q')),
            0.1 * (Input::is_key_pressed('s') - Input::is_key_pressed('z')),
            0.0
        ));
        this->rotate(Vector3(
            0.01 * (Input::is_key_pressed('o') - Input::is_key_pressed('l')),
            0.01 * (Input::is_key_pressed('m') - Input::is_key_pressed('k')),
            0.0
        ));
    }
};

#endif