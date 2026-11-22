#include <charconv>
#include <format>
#include <memory>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <vector>

// 입력 양식의 칸. 모든 칸이 지원할 동작만 정한다(추상 클래스).
class Field
{
public:
    virtual ~Field() = default;
    virtual void set(std::string_view text) = 0;   // 순수 가상 함수
    virtual std::string text() const = 0;
};

class TextField : public Field
{
public:
    void set(std::string_view text) override { m_value = text; }
    std::string text() const override { return m_value.value_or(""); }

private:
    std::optional<std::string> m_value;   // 비어 있음과 빈 문자열을 구별
};

class NumberField : public Field
{
public:
    virtual void set(double value) { m_value = value; }   // 숫자판 추가
    virtual double value() const { return m_value.value_or(0.0); }

    void set(std::string_view text) override { m_value = parse(text); }
    std::string text() const override
    {
        return m_value.has_value() ? std::format("{:.1f}", m_value.value())
                                   : "";
    }

private:
    static double parse(std::string_view text)
    {
        double value{ 0.0 };
        std::from_chars(text.data(), text.data() + text.size(), value);
        return value;
    }
    std::optional<double> m_value;
};

int main()
{
    // Field field;   // 컴파일 오류: 추상 클래스의 객체는 만들 수 없다.

    std::vector<std::unique_ptr<Field>> form;   // 서로 다른 칸을 한데 담는다.
    form.push_back(std::make_unique<TextField>());
    form.push_back(std::make_unique<NumberField>());
    form.push_back(std::make_unique<NumberField>());

    form[0]->set("부엌");
    form[1]->set("21.46");
    // form[2]는 비워 둔다.

    for (const auto& field : form) {   // 실제 타입을 몰라도 같은 방식으로
        std::println("[{}]", field->text());
    }
}
