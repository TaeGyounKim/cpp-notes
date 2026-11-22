#include <print>
#include <vector>

int main()
{
    // int를 담는 vector. 처음에는 원소 두 개
    std::vector<int> numbers{ 11, 22 };
    std::println("크기: {}", numbers.size());

    // 실행 중에 원소를 뒤에 덧붙인다.
    numbers.push_back(33);
    numbers.push_back(44);
    std::println("크기: {}", numbers.size());

    std::println("첫 원소: {}", numbers[0]);
    std::println("마지막 원소: {}", numbers[3]);

    // vector 전체를 한 번에 출력할 수도 있다. (C++23)
    std::println("{}", numbers);

    // 초기화 값이 있으면 꺾쇠괄호를 생략할 수 있다. (C++17)
    std::vector prices{ 4500.0, 3000.5 };
    std::println("{}", prices);
}
