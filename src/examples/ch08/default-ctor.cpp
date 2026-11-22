#include <print>

class Temperature
{
public:
    Temperature() = default;   // 컴파일러가 만드는 기본 생성자를 그대로 쓴다.
    Temperature(double celsius) : m_celsius{ celsius } {}

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius{ 0.0 };
};

// 기본 생성자를 지운 클래스: 객체를 만들 수 없다.
class Units
{
public:
    Units() = delete;
    static double toFahrenheit(double c) { return c * 9.0 / 5.0 + 32.0; }
};

int main()
{
    Temperature room;        // 기본 생성자
    Temperature cold{};      // 기본 생성자 (중괄호)
    // Temperature warm();   // 함수 선언으로 읽힌다(가장 성가신 구문 분석).

    // 배열의 원소는 기본 생성자로 만들어진다.
    Temperature week[7];
    Temperature* days{ new Temperature[3] };
    std::println("{} {} {} {}", room.getCelsius(), cold.getCelsius(),
                 week[6].getCelsius(), days[2].getCelsius());
    delete[] days;
    days = nullptr;

    // Units u;   // 컴파일 오류: 기본 생성자가 지워져 있다.
    std::println("{}F", Units::toFahrenheit(100.0));
}
