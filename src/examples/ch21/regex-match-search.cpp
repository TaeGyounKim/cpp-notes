#include <iostream>
#include <print>
#include <regex>
#include <string>

int main()
{
    // regex_match: 입력 전체가 일치해야 한다. 그룹으로 연·월·일을 꺼낸다.
    const std::regex date{
        R"((\d{4})-(0?[1-9]|1[0-2])-(0?[1-9]|[12]\d|3[01]))" };
    // regex_search: 입력 어딘가에서 일치하는 부분을 찾는다(// 뒤의 주석).
    const std::regex comment{ R"(//\s*(.+)$)" };

    std::string line;
    while (std::getline(std::cin, line)) {
        if (std::smatch m; std::regex_match(line, m, date)) {
            std::println("[날짜] 연 {} 월 {} 일 {} (전체 '{}', 그룹 {}개)",
                         std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]),
                         m[0].str(), m.size() - 1);
        } else if (std::regex_search(line, m, comment)) {
            std::println("[주석] '{}' / 앞부분 '{}' / 위치 {}", m[1].str(),
                         m.prefix().str(), m.position(1));
        } else {
            std::println("[없음] {}", line);
        }
    }
}
