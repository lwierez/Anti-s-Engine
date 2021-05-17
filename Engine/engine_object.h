#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

#include <iostream>
#include <vector>

#include "Maths/geometry.h"

class Mesh
{
public:
    Mesh() {}
    // Create a mesh based on triangles list
    Mesh(std::vector<Triangle>);

    // Get the rotated mesh
    Mesh rotated(Vector3);
    // Get the translated mesh
    Mesh translated(Vector3);

    // Get the list of all triangles in the mesh
    std::vector<Triangle> get_triangles() { return this->triangles; }
    
private:
    // List of the triangles in the mesh
    std::vector<Triangle> triangles;
};

class EngineObject
{
public:
    EngineObject() {}
    EngineObject(Vector3, Vector3, Mesh);

    // Function executed before each render cycle
    virtual void BeforeRender() {};

    // Translate the object according to it rotation
    void translate(Vector3);
    // Apply rotation to the object
    void rotate(Vector3);

    // Return the mesh in world space
    Mesh get_world_mesh();

    void set_position(Vector3 position) { this->position = position; }
    void set_rotation(Vector3 rotation) { this->rotation = rotation; }

    Vector3 get_position() { return this->position; }
    Vector3 get_rotation() { return this->rotation; }

private:
    Mesh mesh;
    Vector3 position;
    Vector3 rotation;
};

#endif