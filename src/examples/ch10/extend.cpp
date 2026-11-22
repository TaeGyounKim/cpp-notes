#include <print>
#include <string>
#include <utility>

class Sensor   // 기반 클래스
{
public:
    explicit Sensor(std::string id) : m_id{ std::move(id) } {}
    const std::string& id() const { return m_id; }

protected:
    // 파생 클래스만 쓰는 도우미: protected
    double lastRaw() const { return m_raw; }
    void storeRaw(double raw) { m_raw = raw; }

private:
    std::string m_id;     // 파생 클래스도 직접 건드리지 못함
    double m_raw{ 0.0 };
};

class Thermometer : public Sensor   // Sensor를 상속(확장)한 파생 클래스
{
public:
    explicit Thermometer(std::string id) : Sensor{ std::move(id) } {}

    void measure(double raw) { storeRaw(raw); }   // protected 멤버 사용
    double celsius() const { return lastRaw() - 0.4; }
    // double peek() const { return m_raw; }   // 오류: private 멤버
};

int main()
{
    Thermometer kitchen{ "T-01" };
    kitchen.measure(22.0);

    // 사용하는 쪽: 파생 클래스 객체는 기반 클래스의 public 멤버도 가진다.
    std::println("{}: {}°C", kitchen.id(), kitchen.celsius());

    // 기반 클래스 참조(포인터)는 파생 클래스 객체를 가리킬 수 있다.
    const Sensor& any{ kitchen };
    std::println("Sensor로 보기: {}", any.id());
    // any.celsius();   // 오류: Sensor에는 celsius()가 없다.
}
