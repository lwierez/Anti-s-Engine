#include <math.h>

#include "Maths/geometry.h"
#include "Maths/matrix.h"

Vector3::Vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(Matrix matrix)
{
    this->x = matrix.get(0, 0);
    this->y = matrix.get(0, 1);
    this->z = matrix.get(0, 2);
}

Vector3 Vector3::add(Vector3 B)
{
    return Vector3(
        this->x + B.x,
        this->y + B.y,
        this->z + B.z
    );
}

Vector3 Vector3::multiply(double k)
{
    return Vector3(
        this->x * k,
        this->y * k,
        this->z * k
    );
}

double Vector3::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector3 Vector3::normalized()
{
    float length = this->length();
    if (length == 0)
        return *this;

    return Vector3(
        this->x / length,
        this->y / length,
        this->z / length
    );
}

Vector3 Vector3::rotated(Vector3 rotation)
{
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

    return this->to_matrix().multiply(x_rotation).multiply(y_rotation).multiply(z_rotation);
}

Matrix Vector3::to_matrix()
{
    Matrix matrix (1, 3);

    matrix.insert(0, 0, this->x);
    matrix.insert(0, 1, this->y);
    matrix.insert(0, 2, this->z);

    return matrix;
}

Triangle::Triangle(Vector3 A, Vector3 B, Vector3 C)
{
    this->a = A;
    this->b = B;
    this->c = C;
}