//
// Created by Jay on 4/5/2026.
//
#include <cassert>
#include <iostream>
#include <core/Matrix.h>

void test_constructors() {
    Matrix a(2, 2);
    assert(a.data[0][0] == 0.0);

    Matrix b(2, 2, 5.0);
    assert(b.data[0][1] == 5.0);
}

void test_addition() {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);
    Matrix c = a + b;
    assert(c.data[0][0] == 3.0);
}

void test_inverse() {
    // TODO
    Matrix a({
        {6, 7},
        {2, 10}
    });
    Matrix a_inverse({
        {0.2174, -0.1522},
        {-0.0435, 0.1304}
    });
}

int main() {
    test_constructors();
    test_addition();

    std::cout << "All tests passed." << std::endl;
    return 0;
}