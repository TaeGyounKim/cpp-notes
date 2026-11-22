#include <iostream>
#include <string>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius(celsius) {}

    // 위임 생성자는 C++11부터
    explicit Temperature(const std::string& text)
        : Temperature(std::stod(text))
    {
    }

    Temperature(const Temperature& src) = default;   // C++11부터

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

int main()
{
    Temperature a(std::string("36.5"));
    Temperature b(a);   // 복사 생성자
    std::cout << b.getCelsius() << '\n';
}
