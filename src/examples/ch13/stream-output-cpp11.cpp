#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

// 스트림과 조작자는 C++98부터 있다. std::quoted는 C++14,
// std::format/println은 C++20/23이므로 C++11에서는 조작자로만 쓴다.
int main()
{
    int code = 42;
    std::cout << '[' << std::setfill('0') << std::setw(6) << code << "]\n";
    std::cout << std::setfill(' ');

    double ratio = 1.23456789;
    std::cout << std::fixed << std::setprecision(2) << ratio << '\n';
    std::cout << std::defaultfloat << std::setprecision(6);   // C++11

    std::cout << std::boolalpha << true << '\n';

    // quoted 대신 직접 따옴표를 붙인다.
    std::string name = "거실";
    std::cout << '"' << name << '"' << '\n';
}
