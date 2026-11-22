#include <print>

int main()
{
    // 구현이 그대로 드러나 있다: 좌석표는 2차원 bool 배열이다.
    bool seats[3][4]{};

    // 쓰는 코드마다 "2차원 배열"이라는 사실에 기대고 있다.
    seats[1][2] = true;
    seats[2][0] = true;

    for (int row{ 0 }; row < 3; ++row) {
        for (int column{ 0 }; column < 4; ++column) {
            std::print("{}", seats[row][column] ? '#' : '.');
        }
        std::println("");
    }

    // 범위를 벗어나도 막아 주는 것이 없다.
    // seats[3][0] = true;   // 미정의 동작
}
