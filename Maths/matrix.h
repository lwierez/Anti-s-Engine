#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    // Create a x * y Matrix
    Matrix(int, int);

    // Insert a double at given position
    void insert(int, int, double);
    // Get element at given position
    double get(int, int);

    // Multiply two matrixes
    Matrix multiply(Matrix);

    void print_matrix();

    int get_x_size() { return this->x_size; }
    int get_y_size() { return this->y_size; }

private:
    double** data;
    int x_size;
    int y_size;
};

#endif