#include <print>

int main()
{
    int a{ 10 + 4 * 3 - 20 / 6 % 3 };
    int b{ 10 + (4 * 3) - ((20 / 6) % 3) };
    std::println("{} {}", a, b);

    // 시프트는 덧셈보다 늦게 계산된다.
    std::println("{}", 1 << 2 + 3);
    std::println("{}", (1 << 2) + 3);
}
