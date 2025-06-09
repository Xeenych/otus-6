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

        for (int r = 0; r < 10; r++) {
            std::cout << std::endl;
            for (int c = 0; c < 10; c++) {
                std::cout << m[r][c] << " ";
            }
        }

        std::cout << std::endl;
        std::cout << m.size() << std::endl;

        for (auto& [val, x, y] : m) {
            std::cout << x << " " << y << " " << val << std::endl;
        }
    }

    return 0;
}