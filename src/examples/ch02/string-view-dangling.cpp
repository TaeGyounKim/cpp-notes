#include <print>
#include <string>
#include <string_view>

using namespace std::string_view_literals;   // "..."sv 를 쓰려면 필요

int main()
{
    std::string name{ "Hello" };

    // 올바른 사용: 살아 있는 문자열을 본다.
    std::string full{ name + " World!" };
    std::string_view good{ full };
    std::println("{}", good);

    // 잘못된 사용: 임시 문자열을 본다.
    // name + " World!" 로 만들어진 임시 문자열은 이 줄이 끝나면 사라진다.
    // std::string_view bad{ name + " World!" };
    // std::println("{}", bad);   // 정의되지 않은 동작

    // sv 리터럴: 문자열 리터럴을 string_view로 만든다.
    auto view{ "My string_view"sv };
    std::println("{} ({}글자)", view, view.size());
}
