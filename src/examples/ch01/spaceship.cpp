#include <compare>
#include <limits>
#include <print>

int main()
{
    int a{ 11 };
    int b{ 20 };

    std::strong_ordering result{ a <=> b };

    if (result == std::strong_ordering::less) { std::println("a가 작다"); }
    if (result == std::strong_ordering::greater) { std::println("a가 크다"); }
    if (result == std::strong_ordering::equal) { std::println("같다"); }

    // 같은 일을 이름 있는 함수로
    if (std::is_lt(result)) { std::println("a가 작다 (is_lt)"); }

    // 부동소수점의 결과 타입은 partial_ordering.
    // NaN이 끼면 순서를 정할 수 없다.
    double nan{ std::numeric_limits<double>::quiet_NaN() };
    std::partial_ordering floatResult{ nan <=> 1.0 };
    std::println("{}", floatResult == std::partial_ordering::unordered);
}
