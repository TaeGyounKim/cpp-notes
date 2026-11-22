#include <print>
#include <string>

int main()
{
    std::string message{ "Hello World!" };

    // 형식 문자열은 컴파일할 때 알 수 있어야 한다.
    // std::println(message);     // 오류
    std::println("{}", message);  // 올바른 방법

    // constexpr 변수는 컴파일할 때 값이 정해지므로 형식 문자열로 쓸 수 있다.
    constexpr auto pattern{ "Value: {}" };
    std::println(pattern, 11);
}
