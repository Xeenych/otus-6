#include "matrix.hpp"

#include <cassert>
// #include <iostream>

int main() {
    // M2
    /*
    {
        constexpr int kDefaultValue = -5;
        Matrix<int, kDefaultValue> matrix;
        assert(0 == matrix.size());

        auto a = matrix[0][0];
        assert(kDefaultValue == a);
        assert(0 == matrix.size());

        matrix[100][100] = 314;
        assert(314 == matrix[100][100]);
        assert(1 == matrix.size());

        matrix[100][100] = kDefaultValue;
        assert(kDefaultValue == matrix[100][100]);
        assert(0 == matrix.size());

        matrix[101][101] = 1;
        matrix[102][102] = 2;

        for (auto e : matrix) {
            std::cout << e.row << " " << e.col << " " << std::endl;
        }
    }
    */

    /*
    {
        Matrix<int, -1> matrix;
        assert(matrix.size() == 0);  // все ячейки свободны
        auto a = matrix[0][0];
        assert(a == -1);
        assert(matrix.size() == 0);
        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);
        // выведется одна строка
        // 100100314
        for (auto c : matrix) {
            size_t x;
            size_t y;
            int v;
            std::tie(x, y, v) = c;
            std::cout << x << y << v << std::endl;
        }
    }
    */

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
    }

    return 0;
}