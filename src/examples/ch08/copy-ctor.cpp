#include <print>
#include <string>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius{ celsius } {}

    // 복사 생성자: 같은 타입 객체를 const 참조로 받는다.
    Temperature(const Temperature& src) : m_celsius{ src.m_celsius }
    {
        std::println("  [복사 생성자] {}", m_celsius);
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

void byValue(Temperature t)   // 인수를 복사해서 매개변수 t를 만든다.
{
    std::println("  byValue 안: {}", t.getCelsius());
}

void byConstRef(const Temperature& t)   // 원본을 참조. 복사 없음
{
    std::println("  byConstRef 안: {}", t.getCelsius());
}

int main()
{
    Temperature noon{ 28.5 };

    std::println("1. 다른 객체로 새 객체 만들기");
    Temperature copy{ noon };

    std::println("2. 값으로 넘기기");
    byValue(noon);

    std::println("3. const 참조로 넘기기");
    byConstRef(noon);

    std::println("copy: {}", copy.getCelsius());
}
