#include <algorithm>
#include <GL/freeglut.h>

#include "Engine/engine.h"
#include "Maths/matrix.h"

double Engine::fovRatio = 1 / tan(3.141 / 2 / 2);
Vector3 Engine::light_position;
EngineObject* Engine::current_camera;
Matrix Engine::projection_matrix = Matrix(3, 3);
std::vector<EngineObject*> Engine::engine_objects;

void Engine::start(int argc, char** argv)
{
    // Create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Anti's Engine");
    // Define the porjection matrix
    Engine::projection_matrix.insert(0, 0, fovRatio * (double)glutGet(GLUT_WINDOW_HEIGHT) / glutGet(GLUT_WINDOW_WIDTH));
    Engine::projection_matrix.insert(1, 1, fovRatio);
    Engine::projection_matrix.insert(2, 2, 10.0 / (10.0 - 1.0));

    // Define the light position
    Engine::light_position = Vector3(-5000, 1000, -5000);

    // Register the rendering function and start the rendering loop
    glutDisplayFunc(render);
    glutMainLoop();
}

void Engine::render(void)
{
    // Update the "x component" of the projection matrix to adapt to screen changes
    Engine::projection_matrix.insert(0, 0, fovRatio * (double)glutGet(GLUT_WINDOW_HEIGHT) / glutGet(GLUT_WINDOW_WIDTH));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Execute all BeforeRender() functions
    Engine::current_camera->BeforeRender();
    for (auto object : engine_objects)
        object->BeforeRender();

    // Register all triangles to render, and sort them to draw the closest points first
    std::vector<Triangle> triangles;
    for (auto object : engine_objects)
    {
        auto transformed_object = object->get_world_mesh().translated(current_camera->get_position().multiply(-1)).rotated(current_camera->get_rotation());
        std::vector<Triangle> transformed_triangles = transformed_object.get_triangles();
        triangles.insert(triangles.end(), transformed_triangles.begin(), transformed_triangles.end());
    }
    std::sort(triangles.begin(), triangles.end(), [](Triangle A, Triangle B) {
        return ((A.a.z + A.b.z + A.c.z) / 3.0) > ((B.a.z + B.b.z + B.c.z) / 3.0);
    });

    // Calculate the light position in camera space
    auto light_position_from_camera_view = light_position.add(current_camera->get_position().multiply(-1)).rotated(current_camera->get_rotation());

    // Render each triangle
    for (auto triangle : triangles)
    {
        // By default every triangle is render. But this boolean will prevent a triangle
        // from being drawn of it is behind the camera or if it is not facing the camera
        bool will_draw = true;

        Vector3 points[3] = {
            triangle.a,
            triangle.b,
            triangle.c
        };

        // Calcultate the triangle center
        Vector3 triangle_center (
            (triangle.a.x + triangle.b.x + triangle.c.x) / 3,
            (triangle.a.y + triangle.b.y + triangle.c.y) / 3,
            (triangle.a.z + triangle.b.z + triangle.c.z) / 3
        );
        // For a triangle ABC, calculate the vectors AB and AC
        Vector3 A(points[1].x - points[0].x, points[1].y - points[0].y, points[1].z - points[0].z),
            B(points[2].x - points[0].x, points[2].y - points[0].y, points[2].z - points[0].z);

        // Calculate the face normal using a cross product and normalise the result
        Vector3 face_normal (
            A.y * B.z - A.z * B.y,
            A.z * B.x - A.x * B.z,
            A.x * B.y - A.y * B.x
        );
        face_normal = face_normal.normalized();

        // Calulate the light incidence vector on the face and normalize the result
        Vector3 light_ray = triangle_center.add(light_position_from_camera_view.multiply(-1)).normalized();

        // Use a dot product to calulate how strong whould the light be on the face
        double light_value = light_ray.x * face_normal.x + light_ray.y * face_normal.y + light_ray.z * face_normal.z;
        light_value = light_value > 0 ? light_value : 0.0;
        glColor3f(.1 + light_value, .1 + light_value * 1.2, .1 + light_value);

        // Create a vector representing the direction from the camera to the rendered triangle
        Vector3 camera_ray = triangle_center.normalized();
        // Prevent the triangle from being drawn if it is not facing the camera
        double camera_ray_dot_product = camera_ray.x * face_normal.x + camera_ray.y * face_normal.y + camera_ray.z * face_normal.z;
        if (camera_ray_dot_product < 0)
            will_draw = false;

        // Project each point
        for (auto& point : points)
        {
            // Prevent the triangle from being drawn if it behind the camera
            if (point.z < 0)
                will_draw = false;

            point = point.to_matrix().multiply(projection_matrix);
            point.x /= point.z;
            point.y /= point.z;
        }

        if (will_draw)
        {
            glBegin(GL_TRIANGLES);
            glVertex2f(points[0].x, points[0].y);
            glVertex2f(points[1].x, points[1].y);
            glVertex2f(points[2].x, points[2].y);
        }
    }

    glEnd();
    glutSwapBuffers();

    glutPostRedisplay();
}