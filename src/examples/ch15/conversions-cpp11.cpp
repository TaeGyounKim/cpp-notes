#include <iostream>
#include <sstream>
#include <string>

// explicit 변환 연산자와 explicit operator bool은 C++11부터 있다.
// operator auto(C++14)와 std::format(C++20)은 쓰지 않는다.
class Celsius
{
public:
    Celsius(double value) : m_value(value) {}
    explicit operator double() const { return m_value; }
    operator std::string() const
    {
        std::ostringstream out;
        out << m_value << "도";
        return out.str();
    }

private:
    double m_value;
};

Celsius operator+(const Celsius& a, const Celsius& b)
{
    return Celsius(static_cast<double>(a) + static_cast<double>(b));
}

int main()
{
    Celsius sum = Celsius(6.6) + 3.4;
    std::string text = sum;
    std::cout << static_cast<double>(sum) << " / " << text << '\n';
}
