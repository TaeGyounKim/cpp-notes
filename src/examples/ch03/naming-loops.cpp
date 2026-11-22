#include <array>
#include <cstddef>
#include <print>

int main()
{
    const std::size_t rowCount{ 2 };
    const std::size_t columnCount{ 3 };
    std::array<std::array<int, columnCount>, rowCount> table{ {
        { 1, 2, 3 },
        { 4, 5, 6 },
    } };

    // i, j 대신 row, column: 어느 쪽이 행이고 열인지 헷갈리지 않는다.
    for (std::size_t row{ 0 }; row < rowCount; ++row) {
        int rowSum{ 0 };
        for (std::size_t column{ 0 }; column < columnCount; ++column) {
            rowSum += table[row][column];
        }
        std::println("{}행의 합: {}", row, rowSum);
    }
}
