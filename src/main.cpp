#include "matrix.hpp"

#include <iostream>

int main() {
    Matrix<int, -2, 1> m;
    //std::cout << "Size:" << m.size() << std::endl;
    //std::cout << m[0] << std::endl;
    //std::cout << m[1] << std::endl;
    //std::cout << m[2] << std::endl;
    //std::cout << "Size:" << m.size() << std::endl;
    m[0] = 0;
    std::cout << "m[0]:" << m[0] << std::endl;
    std::cout << "Size:" << m.size() << std::endl;
    m[0]=-2;
    std::cout << "Size:" << m.size() << std::endl;

    // Matrix<int, -1, 2> m2;

    return 0;
}