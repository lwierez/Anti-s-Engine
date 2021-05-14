#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <GL/freeglut.h>

#include "Maths/geometry.h"
#include "Maths/matrix.h"
#include "Engine/engine.h"
#include "Engine/engine_object.h"

Mesh create_mesh();

int main(int argc, char **argv)
{
    Engine::register_object(EngineObject(
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        create_mesh()
    ));
    Engine::register_object(EngineObject(
        Vector3(0, -10, 0),
        Vector3(0, 0, 0),
        Mesh({
            Triangle(
                Vector3(-10, 0 , -10),
                Vector3(10, 0, 10),
                Vector3(-10, 0, 10)
            ),
            Triangle(
                Vector3(10, 0, 10),
                Vector3(-10, 0, -10),
                Vector3(10, 0, -10)
            )
        })
    ));

    Engine::set_current_camera(EngineObject(
        Vector3(5, 10, -10),
        Vector3(-3.14/4, 0, 0),
        Mesh()
    ));

    Engine::start(argc, argv);

    return 0;
}

Mesh create_mesh()
{
    return Mesh({
        Triangle(
            Vector3(-1.0, 1.0, -1.0), // A
            Vector3(-1.0, -1.0, -1.0), // D
            Vector3(1.0, 1.0, -1.0) // B
        ),
        Triangle(
            Vector3(1.0, -1.0, -1.0), // C
            Vector3(1.0, 1.0, -1.0), // B
            Vector3(-1.0, -1.0, -1.0) // D
        ),
        Triangle(
            Vector3(-1.0, 1.0, 1.0), // F
            Vector3(1.0, 1.0, 1.0), // G
            Vector3(-1.0, -1.0, 1.0) // E
        ),
        Triangle(
            Vector3(1.0, -1.0, 1.0), // H
            Vector3(-1.0, -1.0, 1.0), // E
            Vector3(1.0, 1.0, 1.0) // G
        ),
        Triangle(
            Vector3(-1.0, 1.0, -1.0), // A
            Vector3(-1.0, 1.0, 1.0), // F
            Vector3(-1.0, -1.0, -1.0) // D
        ),
        Triangle(
            Vector3(-1.0, -1.0, 1.0), // E
            Vector3(-1.0, -1.0, -1.0), // D
            Vector3(-1.0, 1.0, 1.0) // F
        ),
        Triangle(
            Vector3(1.0, 1.0, -1.0), // B
            Vector3(1.0, 1.0, 1.0), // G
            Vector3(-1.0, 1.0, -1.0) // A
        ),
        Triangle(
            Vector3(-1.0, 1.0, -1.0), // A
            Vector3(1.0, 1.0, 1.0), // G
            Vector3(-1.0, 1.0, 1.0) // F
        ),
        Triangle(
            Vector3(1.0, -1.0, -1.0), // C
            Vector3(1.0, -1.0, 1.0), // H
            Vector3(1.0, 1.0, -1.0) // B
        ),
        Triangle(
            Vector3(1.0, 1.0, 1.0), // G
            Vector3(1.0, 1.0, -1.0), // B
            Vector3(1.0, -1.0, 1.0) // H
        ),
        Triangle(
            Vector3(-1.0, -1.0, -1.0), // D
            Vector3(-1.0, -1.0, 1.0), // E
            Vector3(1.0, -1.0, -1.0) // C
        ),
        Triangle(
            Vector3(1.0, -1.0, 1.0), // H
            Vector3(1.0, -1.0, -1.0), // C
            Vector3(-1.0, -1.0, 1.0) // E
        ),
    });
}