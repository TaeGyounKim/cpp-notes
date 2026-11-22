#include <print>

class Gauge
{
public:
    explicit Gauge(double value) : m_value{ value }
    {
        std::println("  Gauge가 받은 값: {}", m_value);
    }

private:
    double m_value;
};

class Panel
{
public:
    // 의도: m_scale을 먼저 정하고 그 값으로 m_gauge를 만든다.
    // 실제: 클래스에 선언된 순서(m_gauge 먼저)대로 초기화된다.
    Panel(double scale) : m_scale{ scale }, m_gauge{ m_scale * 10.0 } {}

private:
    Gauge m_gauge;    // 먼저 선언됨 -> 먼저 초기화됨
    double m_scale;   // m_gauge를 만들 때는 아직 초기화 전이다.
};

int main()
{
    Panel panel{ 1.5 };   // 15가 나와야 할 것 같지만...
}
