#include <vector>
#include <cmath>

#include "Engine/engine_object.h"
#include "Maths/geometry.h"

Mesh::Mesh(std::vector<Triangle> triangles)
{
    this->triangles = triangles;
}

Mesh Mesh::rotated(Vector3 rotation)
{
    // Creating the rotation matrixes for the mesh
    Matrix x_rotation (3, 3), y_rotation (3, 3), z_rotation (3, 3);

    x_rotation.insert(0, 0, 1);
    x_rotation.insert(1, 1, cos(rotation.x));
    x_rotation.insert(2, 1, -sin(rotation.x));
    x_rotation.insert(1, 2, sin(rotation.x));
    x_rotation.insert(2, 2, cos(rotation.x));

    y_rotation.insert(0, 0, cos(rotation.y));
    y_rotation.insert(2, 0, sin(rotation.y));
    y_rotation.insert(1, 1, 1);
    y_rotation.insert(0, 2, -sin(rotation.y));
    y_rotation.insert(2, 2, cos(rotation.y));

    z_rotation.insert(0, 0, cos(rotation.z));
    z_rotation.insert(1, 0, -sin(rotation.z));
    z_rotation.insert(0, 1, sin(rotation.z));
    z_rotation.insert(1, 1, cos(rotation.z));
    z_rotation.insert(2, 2, 1);

    // Apply the rotation matrix on every point of every triangle of the mesh
    std::vector<Triangle> rotated_triangles;
    for (auto triangle : this->get_triangles())
        rotated_triangles.push_back(Triangle(
            Vector3(triangle.a.to_matrix().multiply(y_rotation).multiply(x_rotation).multiply(z_rotation)),
            Vector3(triangle.b.to_matrix().multiply(y_rotation).multiply(x_rotation).multiply(z_rotation)),
            Vector3(triangle.c.to_matrix().multiply(y_rotation).multiply(x_rotation).multiply(z_rotation))
        ));

    return Mesh(rotated_triangles);
}

Mesh Mesh::translated(Vector3 translation)
{
    // Translate each point of every triangle of the mesh
    std::vector<Triangle> translated_triangles;
    for (auto triangle : this->get_triangles())
        translated_triangles.push_back(Triangle(
            triangle.a.add(translation),
            triangle.b.add(translation),
            triangle.c.add(translation)
        ));

    return Mesh(translated_triangles);
}

EngineObject::EngineObject(Vector3 position, Vector3 rotation, Mesh mesh)
{
    this->position = position;
    this->rotation = rotation;
    this->mesh = mesh;
}

Mesh EngineObject::get_world_mesh()
{
    return this->mesh.rotated(this->rotation).translated(this->position);
}

void EngineObject::translate(Vector3 translation)
{
    this->position = this->position.add(translation.rotated(Vector3(-this->rotation.x, -this->rotation.y, this->rotation.z)));
}

void EngineObject::rotate(Vector3 rotation)
{
    this->rotation = this->rotation.add(rotation);
}