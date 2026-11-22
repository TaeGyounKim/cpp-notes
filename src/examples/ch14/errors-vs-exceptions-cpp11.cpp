#include <iostream>
#include <stdexcept>
#include <string>

// 예외는 C++98부터 있다. 차이는 출력에 println 대신 cout을 쓰는 것뿐이다.
double parseCelsius(const std::string& text)
{
    if (text.empty()) { throw std::invalid_argument("빈 문자열"); }
    return std::stod(text);   // std::stod는 C++11
}

double average(const std::string& a, const std::string& b)
{
    return (parseCelsius(a) + parseCelsius(b)) / 2;
}

int main()
{
    try {
        std::cout << average("21.5", "23.5") << '\n';
        std::cout << average("21.5", "") << '\n';
    } catch (const std::invalid_argument& e) {
        std::cout << "예외: " << e.what() << '\n';
    }
}
