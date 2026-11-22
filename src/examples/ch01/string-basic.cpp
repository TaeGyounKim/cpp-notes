#include <print>
#include <string>

int main()
{
    std::string greeting{ "Hello, World" };

    std::println("전체: {}", greeting);
    std::println("두 번째 글자: {}", greeting[1]);
    std::println("길이: {}", greeting.size());

    // 기본 타입처럼 대입하고, +로 이어 붙이고, ==로 비교할 수 있다.
    std::string name{ "C++" };
    std::string message{ greeting + " and " + name };
    std::println("{}", message);
    std::println("{}", name == "C++");

    // 글자 하나씩 반복
    for (char letter : name) {
        std::println("[{}]", letter);
    }
}
