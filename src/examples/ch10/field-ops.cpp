#include <format>
#include <print>
#include <string>
#include <utility>

class NumberField
{
public:
    NumberField() = default;
    explicit NumberField(double value) : m_value{ value } {}
    double value() const { return m_value; }
    std::string text() const { return std::format("{:.1f}", m_value); }

private:
    double m_value{ 0.0 };
};

class TextField
{
public:
    TextField() = default;
    explicit TextField(std::string text) : m_text{ std::move(text) } {}
    // 형제 클래스로부터의 변환 생성자(explicit 아님: 암시적 변환 허용)
    TextField(const NumberField& number) : m_text{ number.text() } {}
    const std::string& text() const { return m_text; }

private:
    std::string m_text;
};

// 숫자 + 숫자 = 숫자
NumberField operator+(const NumberField& lhs, const NumberField& rhs)
{
    return NumberField{ lhs.value() + rhs.value() };
}

// 문자열 + 문자열 = 이어 붙인 문자열
TextField operator+(const TextField& lhs, const TextField& rhs)
{
    return TextField{ lhs.text() + rhs.text() };
}

int main()
{
    NumberField a{ 8.4 };
    TextField label{ "현재 " };
    std::println("{}", (a + a).text());       // 16.8
    std::println("{}", (label + a).text());   // a가 TextField로 바뀌어 붙음
}
