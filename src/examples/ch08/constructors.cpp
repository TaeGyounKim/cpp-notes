#include <charconv>
#include <memory>
#include <print>
#include <string_view>

class Temperature
{
public:
    // 생성자: 클래스와 이름이 같고, 반환 타입이 없다.
    Temperature(double celsius)
    {
        std::println("  double 생성자: {}", celsius);
        setCelsius(celsius);
    }

    // 생성자도 여럿 둘 수 있다(오버로딩). 매개변수가 달라야 한다.
    Temperature(std::string_view text)
    {
        std::println("  문자열 생성자: \"{}\"", text);
        setCelsius(parse(text));
    }

    void setCelsius(double celsius) { m_celsius = celsius; }
    double getCelsius() const { return m_celsius; }

private:
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
    std::println("스택");
    Temperature a(18.0);       // 함수 호출 모양
    Temperature b{ 21.5 };     // 균일 초기화
    Temperature c{ "36.5" };   // 문자열 생성자가 골라진다.
    std::println("  {} {} {}", a.getCelsius(), b.getCelsius(),
                 c.getCelsius());

    std::println("자유 저장소");
    auto d{ std::make_unique<Temperature>(-4.0) };   // 인수는 생성자로 간다.
    std::println("  {}", d->getCelsius());

    // a.Temperature(5.0);   // 컴파일 오류: 생성자는 나중에 따로 부를 수 없다.
}
