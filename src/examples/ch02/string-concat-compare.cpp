#include <compare>
#include <print>
#include <string>

int main()
{
    // 이어 붙이기: + 와 +=
    std::string a{ "12" };
    std::string b{ "34" };
    std::string c{ a + b };
    a += b;
    std::println("{} {}", c, a);

    // 비교: 내용을 비교한다. 사전 순서로 크고 작음도 가릴 수 있다.
    std::string hello{ "Hello" };
    std::string world{ "World" };
    std::println("{}", hello == "Hello");
    std::println("{}", hello < world);
    std::println("{}", hello > world);

    // compare(): 음수, 0, 양수를 돌려준다. 같으면 0이라는 점에 주의
    std::println("{}", hello.compare(world) < 0);

    // 삼중 비교 연산자 (C++20)
    auto order{ hello <=> world };
    if (std::is_lt(order)) { std::println("Hello가 앞선다"); }

    // C 스타일 문자열을 == 로 비교하면 주소를 비교한다.
    char first[]{ "12" };
    char second[]{ "12" };
    const char* p1{ first };
    const char* p2{ second };
    std::println("{}", p1 == p2);
}
