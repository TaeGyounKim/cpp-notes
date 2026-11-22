#include <array>
#include <print>

int main()
{
    // <원소의 타입, 원소의 개수>
    std::array<int, 3> scores{ 90, 75, 60 };

    std::println("크기: {}", scores.size());
    std::println("두 번째 원소: {}", scores[1]);

    scores[1] = 80;
    std::println("바꾼 뒤: {}", scores[1]);

    // 초기화 값이 있으면 꺾쇠괄호를 생략할 수 있다. (C++17)
    std::array prices{ 4500, 3000, 12000, 800 };
    std::println("크기: {}", prices.size());
}
