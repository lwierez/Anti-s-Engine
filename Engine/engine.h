#ifndef ENGINE_H
#define ENGINE_H

#include <cmath>

#include "Engine/engine_object.h"

class Engine
{
public:
    // Start the engine. This create a window
    static void start(int, char**);
    // Render function
    static void render(void);

    static void register_object(EngineObject* object) { Engine::engine_objects.push_back(object); }

    static void set_current_camera(EngineObject* camera) { current_camera = camera; }
    static EngineObject* get_current_camera() { return current_camera; }

private:
    // FOV
    static double fovRatio;
    // Position of the light of the scene
    static Vector3 light_position;
    // Object that will be used as the main camera
    static EngineObject* current_camera;
    // Projection matrix to render objects on the screen 
    static Matrix projection_matrix;
    // All objects registered by the engine
    static std::vector<EngineObject*> engine_objects;
};

#endif