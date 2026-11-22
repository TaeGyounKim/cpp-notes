#include <iostream>
#include <string>

class Temperature
{
public:
    Temperature() = default;   // = default는 C++11부터
    explicit Temperature(double celsius) : m_celsius{ celsius } {}

    // string_view(C++17) 대신 const std::string&
    explicit Temperature(const std::string& text) : m_celsius{ std::stod(text) }
    {
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius{ 0.0 };
};

int main()
{
    Temperature a;
    Temperature b{ 21.5 };
    Temperature c{ std::string{ "36.5" } };
    std::cout << a.getCelsius() << ' ' << b.getCelsius() << ' '
              << c.getCelsius() << '\n';
}
