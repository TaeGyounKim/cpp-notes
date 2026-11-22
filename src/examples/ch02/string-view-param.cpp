#include <print>
#include <string>
#include <string_view>

// 읽기만 할 문자열은 std::string_view로 받는다. 값으로 받는다.
std::string_view extension(std::string_view filename)
{
    // rfind: 뒤에서부터 찾는다.
    auto dot{ filename.rfind('.') };
    if (dot == std::string_view::npos) {
        return "";
    }
    // string_view의 substr은 복사하지 않고 string_view를 돌려준다.
    return filename.substr(dot);
}

int main()
{
    // 어떤 종류의 문자열이든 복사 없이 받는다.
    std::string text{ "notes.final.txt" };
    const char* cString{ "photo.png" };

    std::println("{}", extension(text));
    std::println("{}", extension(cString));
    std::println("{}", extension("archive.tar.gz"));
    std::println("[{}]", extension("README"));

    // 길이를 함께 넘기면 널 문자로 끝나지 않는 문자 범위도 볼 수 있다.
    const char* raw{ "data.csv,rest" };
    std::println("{}", extension(std::string_view{ raw, 8 }));
}
