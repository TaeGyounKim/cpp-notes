#include <charconv>
#include <format>
#include <print>
#include <string>
#include <string_view>

class Temperature
{
public:
    void setCelsius(double celsius) { m_celsius = celsius; }
    double getCelsius() const { return m_celsius; }

    // 다른 멤버 함수를 불러서 일을 나눈다.
    void setFahrenheit(double fahrenheit)
    {
        setCelsius((fahrenheit - 32.0) * 5.0 / 9.0);
    }
    double getFahrenheit() const { return getCelsius() * 9.0 / 5.0 + 32.0; }

    // 문자열로 읽고 쓰기. 숫자가 아니면 0으로 둔다.
    void setText(std::string_view text) { m_celsius = parse(text); }
    std::string getText() const { return format(m_celsius); }

private:
    // 도우미 멤버 함수: 밖에서 부를 일이 없으므로 private
    std::string format(double celsius) const
    {
        return std::format("{:.1f}C", celsius);
    }
    double parse(std::string_view text) const
    {
        double value{ 0.0 };
        std::from_chars(text.data(), text.data() + text.size(), value);
        return value;
    }

    double m_celsius{ 0.0 };
};

int main()
{
    Temperature room;
    room.setFahrenheit(77.0);
    std::println("{} = {:.1f}F", room.getText(), room.getFahrenheit());

    room.setText("36.5");
    std::println("{}", room.getText());

    room.setText("hot");   // 숫자가 아니다.
    std::println("{}", room.getText());
}
