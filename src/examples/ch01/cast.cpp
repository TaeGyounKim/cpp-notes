#include <print>

int main()
{
    double price{ 12.87 };

    int a{ (int)price };               // 방법 1: C 스타일
    int b{ int(price) };               // 방법 2: 함수 스타일
    int c{ static_cast<int>(price) };  // 방법 3: static_cast (권장)
    std::println("{} {} {}", a, b, c);

    // 반올림이 아니라 버림이다. 음수도 0 쪽으로 버려진다.
    std::println("{}", static_cast<int>(-12.87));
}
