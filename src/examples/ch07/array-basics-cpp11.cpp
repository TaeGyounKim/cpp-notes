#include <cstddef>
#include <iostream>

int main()
{
    std::size_t count{ 4 };
    // new int[]{ ... }처럼 크기를 생략하는 형태(C++20) 대신 크기를 적는다.
    int* scores{ new int[4]{ 90, 85 } };
    for (std::size_t i{ 0 }; i < count; ++i) {
        std::cout << scores[i] << ' ';
    }
    std::cout << '\n';
    delete[] scores;
    scores = nullptr;
}
