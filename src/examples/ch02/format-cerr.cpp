#include <iostream>
#include <print>

int main()
{
    int code{ 404 };

    std::println("표준 출력으로 나간다: {}", code);

    // 첫 인수로 스트림을 주면 그곳으로 출력한다.
    std::println(std::cerr, "표준 오류로 나간다: {}", code);
}
