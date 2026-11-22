#include <print>

int main()
{
    int score{ 72 };

    // 조건 ? 참일 때의 값 : 거짓일 때의 값
    std::println("{}", score >= 60 ? "합격" : "불합격");

    // 식이므로 값이 필요한 자리 어디에나 쓸 수 있다.
    int bonus{ score >= 90 ? 1000 : 0 };
    std::println("{}", bonus);
}
