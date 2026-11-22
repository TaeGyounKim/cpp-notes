#include <cstdint>
#include <iostream>

// cmp_*(C++20), <bit>(C++20), <numbers>(C++20), gcd/lcm(C++17)가 없으므로
// 직접 쓴다. 이런 작은 도구들이 표준에 들어오면서 손으로 쓸 일이 줄었다.
bool cmpGreater(int a, unsigned b)
{
    return a >= 0 && static_cast<unsigned>(a) > b;
}

int popcount(std::uint8_t x)
{
    int n = 0;
    while (x != 0) { n += x & 1u; x = static_cast<std::uint8_t>(x >> 1); }
    return n;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    const double pi = 3.141592653589793;
    std::cout << std::boolalpha << cmpGreater(-1, 0u) << ' '
              << popcount(0xEB) << ' ' << gcd(12, 18) << ' ' << pi << '\n';
}
