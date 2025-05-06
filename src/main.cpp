#include "matrix.hpp"

#include <cassert>
#include <iostream>

int main() {
    Matrix<int, -1> matrix;
    assert(0 == matrix.size());

    auto a = matrix[0][0];
    assert(-1 == a);
    assert(0 == matrix.size());

    matrix[100][100] = 314;
    assert(314 == matrix[100][100]);
    assert(1 == matrix.size());

    for (auto c : matrix) {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}