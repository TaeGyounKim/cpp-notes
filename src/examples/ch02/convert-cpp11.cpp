#include <iostream>
#include <sstream>
#include <string>

int main()
{
    // std::to_string, std::stoi 계열은 C++11에서 들어왔다.
    std::string count{ std::to_string(42) };
    int number{ std::stoi("123") };
    std::cout << count << ' ' << number + 1 << '\n';

    // <charconv>(C++17) 대신: 문자열 스트림
    std::ostringstream out;
    out << 12345;
    std::string text{ out.str() };

    std::istringstream in{ "678" };
    int parsed{};
    in >> parsed;

    std::cout << text << ' ' << parsed << '\n';
}
