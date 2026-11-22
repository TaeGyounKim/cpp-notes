#include <print>

#define SQUARE_GOOD(x) ((x) * (x))   // 끝에 세미콜론을 붙이지 않는다.
#define SQUARE_BAD(x) (x * x)        // 괄호를 빠뜨린 매크로

int calls{ 0 };
int expensive()
{
    ++calls;   // 몇 번 불렸는지 센다.
    return 4;
}

constexpr int square(int x) { return x * x; }   // 매크로 대신 쓸 함수

int main()
{
    std::println("SQUARE_GOOD(2 + 3) = {}", SQUARE_GOOD(2 + 3));   // 25
    std::println("SQUARE_BAD(2 + 3)  = {}", SQUARE_BAD(2 + 3));    // 11!
    // SQUARE_BAD(2 + 3)는 (2 + 3 * 2 + 3)으로 그대로 바뀐다.

    calls = 0;
    int a{ SQUARE_GOOD(expensive()) };   // expensive()가 두 번 불린다.
    std::println("매크로: {} (expensive {}번)", a, calls);

    calls = 0;
    int b{ square(expensive()) };        // 인수를 한 번만 계산한다.
    std::println("함수: {} (expensive {}번)", b, calls);
}
