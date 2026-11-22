#include <print>
#include <utility>

int main()
{
    // 타입이 달라도 되는 값 두 개의 묶음
    std::pair<double, int> item{ 1.5, 3 };
    std::println("{} {}", item.first, item.second);

    item.second = 4;
    std::println("{} {}", item.first, item.second);

    // 초기화 값이 있으면 꺾쇠괄호를 생략할 수 있다. (C++17)
    std::pair point{ 10, 'A' };
    std::println("{} {}", point.first, point.second);
}
