#include "matrix.hpp"

#include <iostream>

int main() {
    {
        Matrix<int, 0> m;
        for (int r = 0; r < 10; r++) {
            m[r][r] = r;
        }

        for (int r = 0; r < 10; r++) {
            m[r][9 - r] = 9 - r;
        }

        for (int r = 1; r < 9; r++) {
            std::cout << std::endl;
            for (int c = 1; c < 9; c++) {
                std::cout << m[r][c] << " ";
            }
        }

        std::cout << std::endl;
        std::cout << m.size() << std::endl;

        ((m[100][100] = 314) = 0) = 217;

        std::cout << m[100][100] << std::endl;
    }

    return 0;
}