#include <print>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius{ celsius } {}

    // 대입 연산자: 이미 있는 객체에 다른 객체의 값을 덮어쓴다.
    Temperature& operator=(const Temperature& rhs)
    {
        if (this == &rhs) {   // 자기 대입이면 아무것도 하지 않는다.
            std::println("  [자기 대입]");
            return *this;
        }
        std::println("  [대입] {} <- {}", m_celsius, rhs.m_celsius);
        m_celsius = rhs.m_celsius;
        return *this;         // 이 객체의 참조를 돌려준다.
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

int main()
{
    Temperature a{ 10.0 };
    Temperature b{ 20.0 };
    Temperature c{ 30.0 };

    std::println("a = b = c;");
    a = b = c;   // a.operator=(b.operator=(c))
    std::println("결과: {} {} {}", a.getCelsius(), b.getCelsius(),
                 c.getCelsius());

    std::println("a = a;");
    a = a;
}
