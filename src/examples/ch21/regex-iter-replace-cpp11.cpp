#include <iostream>
#include <regex>
#include <string>
#include <vector>

// 정규식 반복자와 regex_replace는 C++11부터 있다.
// 컨테이너 출력(C++23)이 없으므로 반복문으로 출력한다.
int main()
{
    const std::string log = "kitchen=24.5; living=22.0";
    const std::regex pair(R"((\w+)=([\d.]+))");

    const std::sregex_iterator end;
    for (std::sregex_iterator it(log.begin(), log.end(), pair); it != end;
         ++it) {
        std::cout << (*it)[1] << ':' << (*it)[2] << ' ';
    }
    std::cout << '\n';

    const std::regex sep(R"(\s*[,;]\s*)");
    std::vector<std::string> fields(
        std::sregex_token_iterator(log.begin(), log.end(), sep, -1),
        std::sregex_token_iterator());
    std::cout << fields.size() << ' '
              << std::regex_replace(log, pair, "$1 is $2") << '\n';
}
