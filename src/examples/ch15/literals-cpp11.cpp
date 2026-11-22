#include <cstddef>
#include <iostream>
#include <string>

// 사용자 정의 리터럴은 C++11부터 있다.
// 표준 리터럴(s, min, i 등)은 C++14, sv는 C++17이라 쓰지 않는다.
// C++11에서는 ""와 _ 사이에 공백을 두는 옛 문법(operator "" _km)도 쓰였다.
class Length
{
public:
    explicit Length(long double meters) : m_meters(meters) {}
    long double meters() const { return m_meters; }

private:
    long double m_meters;
};

Length operator"" _km(long double d) { return Length(d * 1000); }

std::string operator"" _str(const char* text, std::size_t length)
{
    return std::string(text, length);
}

int main()
{
    Length a = 1.2_km;
    std::string s = "센서"_str;
    std::cout << a.meters() << "m " << s.size() << '\n';
}
