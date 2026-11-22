#include <print>
#include <string>

class Temperature
{
public:
    // 기본 생성자가 없다. double을 꼭 받아야 만들 수 있다.
    explicit Temperature(double celsius) : m_celsius{ celsius } {}
    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

class Sensor
{
public:
    // 생성자 초기화 목록: 콜론 뒤, 본문 { 앞. 멤버가 "만들어질 때" 값을 준다.
    Sensor(int id, const std::string& room, double start)
        : m_id{ id }, m_room{ room }, m_last{ start }
    {
        // 여기서 m_id = id;로 대입하려 하면 컴파일 오류(const)
    }

    void print() const
    {
        std::println("센서 {} ({}): {}", m_id, m_room, m_last.getCelsius());
    }

private:
    const int m_id;             // const 멤버: 초기화 목록에서만 값을 준다.
    const std::string& m_room;  // 참조 멤버: 만들 때 대상을 정한다.
    Temperature m_last;         // 기본 생성자가 없는 멤버 객체
};

int main()
{
    std::string kitchen{ "부엌" };
    Sensor sensor{ 7, kitchen, 23.5 };
    sensor.print();
}
