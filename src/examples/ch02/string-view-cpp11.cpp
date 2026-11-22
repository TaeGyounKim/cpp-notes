#include <iostream>
#include <string>

// std::string_view(C++17) 대신: const std::string& 로 받는다.
// 문자열 리터럴을 넘기면 임시 std::string이 만들어져 복사가 한 번 일어난다.
std::string extension(const std::string& filename)
{
    std::string::size_type dot{ filename.rfind('.') };
    if (dot == std::string::npos) {
        return "";
    }
    return filename.substr(dot);   // 새 문자열을 만들어 돌려준다.
}

int main()
{
    std::string text{ "notes.final.txt" };
    std::cout << extension(text) << '\n';
    std::cout << extension("archive.tar.gz") << '\n';
}
