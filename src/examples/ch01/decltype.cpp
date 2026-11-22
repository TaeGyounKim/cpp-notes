#include <print>
#include <string>

const std::string message{ "Test" };

const std::string& getMessage()
{
    return message;
}

int main()
{
    int x{ 123 };
    decltype(x) y{ 456 };   // x의 타입, 즉 int
    std::println("{} {}", x, y);

    // auto는 참조와 const를 떼어 내고, decltype은 그대로 둔다.
    auto a{ getMessage() };                 // std::string (복사본)
    decltype(getMessage()) b{ getMessage() };   // const std::string&

    std::println("a는 같은 객체인가: {}", &a == &message);
    std::println("b는 같은 객체인가: {}", &b == &message);
}
