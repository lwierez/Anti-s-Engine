#include <iostream>

#include "Maths/matrix.h"

Matrix::Matrix (int x_size, int y_size)
{
    this->x_size = x_size;
    this->y_size = y_size;

    this->data = new double* [y_size];
    for (int y = 0 ; y < y_size ; y++)
    {
        this->data[y] = new double[x_size];
        for (int x = 0 ; x < x_size ; x++)
            this->data[y][x] = 0;
    }
}

void Matrix::insert(int x, int y, double data)
{
    this->data[y][x] = data;
}

double Matrix::get(int x, int y)
{
    return this->data[y][x];
}

Matrix Matrix::multiply(Matrix B)
{
    if (this->get_y_size() != B.get_x_size())
        return Matrix(0, 0);

    Matrix C (this->get_x_size(), B.get_y_size());

    for (int y = 0 ; y < C.get_y_size() ; y++)
        for (int x = 0 ; x < C.get_x_size() ; x++)
        {
            double data = 0;

            for (int i = 0 ; i < this->get_y_size() ; i++)
                data += this->get(x, i) * B.get(i, y);

            C.insert(x, y, data);
        }
    
    return C;
}

void Matrix::print_matrix()
{
    for (int y = 0 ; y < this->y_size ; y++)
    {
        for (int x = 0 ; x < this->x_size; x++)
        {
            std::cout << this->get(x, y) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}