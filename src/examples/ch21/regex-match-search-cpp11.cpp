#include <iostream>
#include <regex>
#include <string>

// if 초기화문(C++17)과 println(C++23)이 없으므로 smatch를 바깥에 선언한다.
// regex_match, regex_search, smatch는 C++11부터 있다.
int main()
{
    const std::regex date(R"((\d{4})-(\d{1,2})-(\d{1,2}))");
    const std::regex comment(R"(//\s*(.+)$)");
    std::string line;
    while (std::getline(std::cin, line)) {
        std::smatch m;
        if (std::regex_match(line, m, date)) {
            std::cout << "[날짜] " << m[1] << '/' << m[2] << '/' << m[3]
                      << '\n';
        } else if (std::regex_search(line, m, comment)) {
            std::cout << "[주석] " << m[1] << '\n';
        } else {
            std::cout << "[없음] " << line << '\n';
        }
    }
}
