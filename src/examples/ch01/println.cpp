#include <print>

int main()
{
    std::println("사과 {}개와 배 {}개", 3, 2);
    std::println("{} + {} = {}", 3, 2, 3 + 2);

    std::print("print는 ");
    std::print("줄을 바꾸지 ");
    std::println("않습니다.");
}
