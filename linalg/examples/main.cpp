#include <iostream>
#include <vector>
#include <core/Matrix.h>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.



int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    std::cout << "Zero Matrix" << std::endl;
    Matrix mtx = Matrix(3, 3);
    mtx.print();

    std::cout << "Ones Matrix" << std::endl;
    Matrix mtx_one = Matrix(3, 3, 1);
    mtx_one.print();

    std::cout << "Matrix Addition" << std::endl;
    Matrix addition = mtx + mtx_one;
    addition.print();

    std::cout << "Matrix Subtraction" << std::endl;
    Matrix subtraction = mtx - mtx_one;
    subtraction.print();

    // Create some complex matrix
    Matrix2D complex_matrix = {
        {1, 2, 3, 4},
        {4, 2, 6, 8},
        {6, 7, 3, 9}
    };
    Matrix2D complex_matrix2 = {
        {34, 56, 22, 67},
        {31, 36, 87, 69},
        {54, 56, 73, 11}
    };
    Matrix cmpl = Matrix(complex_matrix);
    Matrix cmpl2 = Matrix(complex_matrix2);
    Matrix sum = cmpl + cmpl2;
    std::cout << "Sum Matrix" << std::endl;
    sum.print();

    Matrix difference = cmpl - cmpl2;
    std::cout << "Difference Matrix" << std::endl;
    difference.print();

    std::cout << "Transpose" << std::endl;
    std::cout << "Before" << std::endl;
    cmpl.print();
    Matrix transposed_matrix = cmpl.transpose();
    std::cout << "Transpose Matrix" << std::endl;
    transposed_matrix.print();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}