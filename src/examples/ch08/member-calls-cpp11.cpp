#include <iostream>
#include <sstream>
#include <string>

class Temperature
{
public:
    void setCelsius(double celsius) { m_celsius = celsius; }
    double getCelsius() const { return m_celsius; }

    void setFahrenheit(double fahrenheit)
    {
        setCelsius((fahrenheit - 32.0) * 5.0 / 9.0);
    }

    // string_view(C++17) 대신 const std::string&로 받는다.
    void setText(const std::string& text) { m_celsius = parse(text); }
    std::string getText() const { return format(m_celsius); }

private:
    // std::format(C++20) 대신 문자열 스트림으로 만든다.
    std::string format(double celsius) const
    {
        std::ostringstream out;
        out.setf(std::ios::fixed);
        out.precision(1);
        out << celsius << 'C';
        return out.str();
    }
    // from_chars(C++17) 대신 문자열 스트림으로 읽는다.
    double parse(const std::string& text) const
    {
        std::istringstream in{ text };
        double value{ 0.0 };
        if (!(in >> value)) {
            return 0.0;
        }
        return value;
    }

    double m_celsius{ 0.0 };   // 클래스 안 멤버 초기화는 C++11부터
};

int main()
{
    Temperature room;
    room.setFahrenheit(77.0);
    std::cout << room.getText() << '\n';
    room.setText("hot");
    std::cout << room.getText() << '\n';
}
