#include <print>
#include <string>

int main()
{
    std::string path{ "photos/summer.png" };

    // substr(시작 위치, 길이): 부분 문자열
    std::println("{}", path.substr(0, 6));
    std::println("{}", path.substr(7));     // 길이를 생략하면 끝까지

    // find: 찾은 위치. 못 찾으면 std::string::npos
    auto dot{ path.find(".") };
    if (dot != std::string::npos) {
        std::println("점의 위치: {}", dot);
        // replace(시작 위치, 길이, 새 문자열)
        path.replace(dot, 4, ".jpg");
    }
    std::println("{}", path);

    std::println("{}", path.starts_with("photos/"));   // C++20
    std::println("{}", path.ends_with(".png"));        // C++20
    std::println("{}", path.contains("summer"));       // C++23
    std::println("{}", path.contains('#'));            // C++23
}
