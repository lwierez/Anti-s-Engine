#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Maths/matrix.h"

class Vector3
{
public:
    double x, y, z;

    Vector3() { this->x = this->y = this-> z = 0; }
    Vector3(double, double, double);
    Vector3(Matrix);

    Vector3 add(Vector3);
    Vector3 multiply(double);

    double length();
    Vector3 normalized();
    Vector3 rotated(Vector3);

    Matrix to_matrix();
};

class Triangle
{
public:
    Vector3 a, b, c;

    Triangle() {}
    Triangle(Vector3, Vector3, Vector3);
};

#endif