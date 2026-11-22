#include <print>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius{ celsius } {}

    Temperature(const Temperature& src) : m_celsius{ src.m_celsius }
    {
        std::println("    -> 복사 생성자");
    }

    Temperature& operator=(const Temperature& rhs)
    {
        std::println("    -> 대입 연산자");
        m_celsius = rhs.m_celsius;
        return *this;
    }

private:
    double m_celsius;
};

Temperature makeNoon()
{
    return Temperature{ 28.5 };
}

int main()
{
    Temperature a{ 1.0 };

    std::println("Temperature b{{ a }};");
    Temperature b{ a };

    std::println("Temperature c = a;");   // =가 있어도 선언이다.
    Temperature c = a;

    std::println("b = c;");               // 이미 있는 b에 대입
    b = c;

    std::println("Temperature d = makeNoon();");
    Temperature d = makeNoon();           // 복사 생략: 아무것도 불리지 않음

    std::println("d = makeNoon();");
    d = makeNoon();                       // 임시 객체를 d에 대입
}
