#include <format>
#include <iostream>
#include <print>
#include <string>

int main()
{
    int width{ 1920 };
    int height{ 1080 };

    // std::format: 문자열을 만들어 돌려준다. (C++20)
    std::string text{ std::format("{} x {}", width, height) };
    std::cout << text << '\n';

    // std::print / std::println: 만들어서 바로 출력한다. (C++23)
    std::print("{} x {}", width, height);
    std::println(" 화면");

    // 중괄호 자체를 출력하려면 두 번 적는다.
    std::println("{{{}}}", width);

    // 값만 출력할 때도 형식 문자열은 꼭 있어야 한다.
    std::println("{}", width);
    std::println("");   // 빈 줄
}
