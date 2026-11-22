#include <cstddef>
#include <iostream>

void doubleAll(int values[], std::size_t size)
{
    for (std::size_t i{ 0 }; i < size; ++i) {
        values[i] *= 2;
    }
}

int main()
{
    int scores[]{ 5, 7, 9, 11 };
    // std::size(C++17) 대신 sizeof로 원소 수를 구한다.
    const std::size_t count{ sizeof(scores) / sizeof(scores[0]) };
    doubleAll(scores, count);
    for (int score : scores) {
        std::cout << score << ' ';
    }
    std::cout << '\n';
}
