#include <print>
#include <string>
#include <vector>

using namespace std::string_literals;   // "..."s 를 쓰려면 필요

int main()
{
    auto a{ "Hello" };    // const char*
    auto b{ "Hello"s };   // std::string

    // std::println("{}", a.size());   // 오류: 포인터에는 size()가 없다.
    std::println("{} {}", a, b.size());

    // CTAD의 함정: 원소가 const char* 인 벡터가 된다.
    std::vector wrong{ "Kim", "Lee", "Park" };

    // s를 붙이면 std::string의 벡터가 된다.
    std::vector names{ "Kim"s, "Lee"s, "Park"s };
    std::println("{}", names[0].size());
    std::println("{}", names[0] + "!");

    // wrong의 원소는 포인터라서 size()도 + 도 쓸 수 없다.
    std::println("{}", wrong[0]);
}
