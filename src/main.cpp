#include "matrix.hpp"

#include <cassert>
#include <iostream>

int main() {
    // M1
    {
        constexpr int kDefaultValue = -2;
        Matrix<int, kDefaultValue, 1> matrix;
        assert(0 == matrix.size());

        auto a1 = matrix[0];
        assert(kDefaultValue == a1);
        assert(0 == matrix.size());

        matrix[100] = 314;
        assert(314 == matrix[100]);
        assert(1 == matrix.size());

        matrix[100] = kDefaultValue;
        assert(kDefaultValue == matrix[100]);
        assert(0 == matrix.size());


        auto b = matrix.begin();
    }

    // M2
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
    }

    /*
    for (auto c : matrix) {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    */
    /*
        Matrix<int, -2, 1> m1;
        auto b = m1.begin();
        m1[0] = 10;
        int v = *b;
        std::cout << v << std::endl;
        std::cout << m1.size() << std::endl;

        auto begin = m1.begin();
        std::cout << *begin << std::endl;
        auto end =begin.next();
        //assert(begin == end);
        */
    /*
    for (auto vv: m1) {
        std::cout << vv << std::endl;
    }
    */

    return 0;
}