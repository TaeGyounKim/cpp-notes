#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

// span(C++20)과 mdspan(C++23)이 없으므로 포인터와 길이를 넘기고,
// 2차원 첨자는 직접 계산한다.
int total(const int* values, std::size_t n)
{
    int sum = 0;
    for (std::size_t i = 0; i < n; ++i) { sum += values[i]; }
    return sum;
}

int main()
{
    std::vector<int> v = { 11, 22, 33, 44, 55, 66 };
    std::array<int, 5> arr = {{ 5, 4, 3, 2, 1 }};
    int carr[] = { 9, 8, 7 };
    std::cout << total(v.data(), v.size()) << ' '
              << total(arr.data(), arr.size()) << ' '
              << total(carr, sizeof(carr) / sizeof(carr[0])) << ' '
              << total(v.data() + 2, 3) << '\n';

    std::vector<int> cells = { 1, 2, 3, 4, 5, 6, 7, 8 };
    const std::size_t rows = 2, cols = 4;
    for (std::size_t r = 0; r < rows; ++r) {          // 행 우선: r * cols + c
        for (std::size_t c = 0; c < cols; ++c) {
            std::cout << cells[r * cols + c];
        }
        std::cout << ' ';
    }
    for (std::size_t r = 0; r < rows; ++r) {          // 열 우선: c * rows + r
        for (std::size_t c = 0; c < cols; ++c) {
            std::cout << cells[c * rows + r];
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}
