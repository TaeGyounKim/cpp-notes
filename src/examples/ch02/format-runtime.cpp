#include <cstdio>   // stdout
#include <format>
#include <print>
#include <string>
#include <string_view>

enum class Language { English, Korean };

// 형식 문자열이 실행 중에 정해진다.
std::string_view localizedFormat(Language language)
{
    switch (language) {
        case Language::English:
            return "Numbers: {0} and {1}.";
        case Language::Korean:
            return "숫자: {0}, {1}";
    }
    return "";
}

int main()
{
    int first{ 1 };
    int second{ 2 };

    // 실행 중에 정해지는 형식 문자열은 vprint_unicode로 출력한다.
    // 인수는 std::make_format_args로 묶어서 넘긴다.
    std::vprint_unicode(stdout, localizedFormat(Language::English),
                        std::make_format_args(first, second));
    std::println("");
    std::vprint_unicode(stdout, localizedFormat(Language::Korean),
                        std::make_format_args(first, second));
    std::println("");

    // 문자열로 받고 싶으면 std::vformat
    std::string text{ std::vformat(localizedFormat(Language::Korean),
                                   std::make_format_args(first, second)) };
    std::println("[{}]", text);

    // 형식 문자열이 잘못되면 실행 중에 std::format_error 예외가 던져진다.
    try {
        std::string broken{ std::vformat("An integer: {5}",
                                         std::make_format_args(first)) };
        std::println("{}", broken);
    } catch (const std::format_error& exception) {
        std::println("format_error: {}", exception.what());
    }
}
