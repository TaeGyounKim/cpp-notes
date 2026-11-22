#include <print>

int main()
{
    int a{ 17 };
    int b{ 5 };

    std::println("a + b = {}", a + b);
    std::println("a - b = {}", a - b);
    std::println("a * b = {}", a * b);
    std::println("a / b = {}", a / b);   // 정수끼리 나누면 몫만 남는다.
    std::println("a % b = {}", a % b);   // 나머지
    std::println("17.0 / 5 = {}", 17.0 / 5);

    int n{ 10 };
    int post{ n++ };   // post에는 올리기 전의 값이 들어간다.
    int pre{ ++n };    // pre에는 올린 뒤의 값이 들어간다.
    std::println("post={} pre={} n={}", post, pre, n);

    n += 8;   // n = n + 8
    n /= 3;   // n = n / 3
    n %= 4;   // n = n % 4
    std::println("n={}", n);

    bool ready{ false };
    std::println("!ready = {}", !ready);
}
