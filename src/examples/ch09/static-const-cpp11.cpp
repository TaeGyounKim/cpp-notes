#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius(celsius), m_reads(0) {}

    double celsius() const
    {
        ++m_reads;
        return m_celsius;
    }
    std::string text() const
    {
        ++m_reads;
        return format(m_celsius);
    }
    unsigned reads() const { return m_reads; }

    // string_view와 from_chars(C++17) 대신 const std::string&와 strtod
    void setText(const std::string& text)
    {
        m_celsius = std::strtod(text.c_str(), nullptr);
    }

    static double toFahrenheit(double celsius)
    {
        return celsius * 9.0 / 5.0 + 32.0;
    }

private:
    static std::string format(double value)   // std::format(C++20) 대신
    {
        std::ostringstream out;
        out.precision(1);
        out << std::fixed << value << "C";
        return out.str();
    }

    double m_celsius;
    mutable unsigned m_reads;
};

int main()
{
    Temperature room(21.5);
    const Temperature& view = room;
    std::cout << view.text() << " = "
              << Temperature::toFahrenheit(view.celsius()) << "F\n";
    room.setText("23.4");
    std::cout << room.text() << ", 읽은 횟수 " << room.reads() << '\n';
}
