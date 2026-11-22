#include <print>
#include <string>

class Temperature
{
public:
    Temperature(double celsius) : m_celsius{ celsius }
    {
        std::println("  double 생성자가 {}로 만듦", celsius);
    }

    // 버그: 다른 생성자에 일을 맡기려 했다.
    Temperature(const std::string& text)
    {
        // 이 줄은 이 객체를 초기화하지 않는다.
        // 이름 없는 임시 Temperature를 하나 만들었다가 바로 버린다.
        Temperature(std::stod(text));
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius{ 0.0 };
};

int main()
{
    Temperature t{ std::string{ "36.5" } };
    std::println("t의 값: {}", t.getCelsius());   // 36.5가 아니다.
}
