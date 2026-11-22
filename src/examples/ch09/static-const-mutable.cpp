#include <charconv>
#include <format>
#include <print>
#include <string>
#include <string_view>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius{ celsius } {}

    // const 멤버 함수: 객체를 바꾸지 않겠다는 약속
    double celsius() const
    {
        ++m_reads;   // mutable 멤버는 const 함수 안에서도 바꿀 수 있다.
        return m_celsius;
    }
    std::string text() const
    {
        ++m_reads;
        return format(m_celsius);   // static 멤버 함수 호출
    }
    unsigned reads() const { return m_reads; }

    void setText(std::string_view text) { m_celsius = parse(text); }

    // public static 멤버 함수: 객체 없이 클래스 이름으로 부른다.
    static double toFahrenheit(double celsius)
    {
        return celsius * 9.0 / 5.0 + 32.0;
    }

private:
    // 특정 객체의 데이터를 쓰지 않는 도우미: static
    static std::string format(double value)
    {
        return std::format("{:.1f}°C", value);
    }
    static double parse(std::string_view text)
    {
        double value{ 0.0 };
        std::from_chars(text.data(), text.data() + text.size(), value);
        return value;
    }

    double m_celsius;
    mutable unsigned m_reads{ 0 };   // 읽은 횟수: 겉으로 보이는 값이 아님
};

void show(const Temperature& t)   // const 참조: const 멤버 함수만 부를 수 있다.
{
    std::println("{} = {}°F", t.text(), Temperature::toFahrenheit(t.celsius()));
    // t.setText("20");   // 컴파일 오류: const 객체에 비const 함수
}

int main()
{
    Temperature room{ 21.5 };
    show(room);
    room.setText("23.4");   // 비const 객체는 둘 다 부를 수 있다.
    show(room);
    std::println("읽은 횟수: {}", room.reads());
    std::println("100°C = {}°F", Temperature::toFahrenheit(100.0));
}
