#include <iostream>
#include <regex>
#include <string>

// <regex>와 날 문자열 리터럴은 C++11부터 있다.
// println(C++23) 대신 cout을 쓴다.
int main()
{
    std::regex phone(R"(\d{3}-\d{4})");
    std::regex backref(R"((\d+)-.*-\1)");
    std::cout << std::boolalpha << std::regex_match("555-1234", phone) << ' '
              << std::regex_match("12-ab-12", backref) << ' '
              << std::regex_match("12-ab-21", backref) << '\n';

    std::smatch m;
    std::string text = "aaabbb";
    std::regex_match(text, m, std::regex(R"((a+?)(ab)*(b+))"));
    std::cout << m[1] << ' ' << m[2] << ' ' << m[3] << '\n';
}
