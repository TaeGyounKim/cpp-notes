#include <bitset>
#include <cmath>
#include <iostream>
#include <limits>

int main()
{
    // 형변환과 연산자는 C++11에서도 그대로다.
    double price{ 12.87 };
    int whole{ static_cast<int>(price) };
    std::cout << whole << '\n';
    std::cout << 17 / 5 << ' ' << 17 % 5 << '\n';

    // 2진수 리터럴이 없으므로 16진수로 적는다. 0xC = 1100, 0xA = 1010
    unsigned int a{ 0xC };
    unsigned int b{ 0xA };

    // 2진수로 출력: std::bitset<자릿수>
    std::cout << std::bitset<4>(a & b) << '\n';
    std::cout << std::bitset<4>(a | b) << '\n';
    std::cout << std::bitset<4>(a ^ b) << '\n';

    // std::boolalpha: bool을 1/0 대신 true/false로 출력
    double inf{ std::numeric_limits<double>::infinity() };
    std::cout << std::boolalpha << std::isinf(inf) << '\n';
}
