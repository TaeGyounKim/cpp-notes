#include <print>
#include <string>

class Temperature
{
public:
    // 대상 생성자
    explicit Temperature(double celsius) : m_celsius{ celsius }
    {
        std::println("  1) double 생성자 본문: {}", m_celsius);
    }

    // 위임 생성자: 초기화 목록에서 같은 클래스의 다른 생성자를 부른다.
    explicit Temperature(const std::string& text)
        : Temperature{ std::stod(text) }   // 목록에 이것 하나만 올 수 있다.
    {
        std::println("  2) 문자열 생성자 본문");
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

int main()
{
    Temperature t{ std::string{ "36.5" } };
    std::println("t의 값: {}", t.getCelsius());
}
