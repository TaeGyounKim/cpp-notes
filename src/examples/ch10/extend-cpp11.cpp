#include <iostream>
#include <string>
#include <utility>

class Sensor
{
public:
    explicit Sensor(std::string id) : m_id(std::move(id)) {}
    const std::string& id() const { return m_id; }

protected:
    double lastRaw() const { return m_raw; }
    void storeRaw(double raw) { m_raw = raw; }

private:
    std::string m_id;
    double m_raw = 0.0;
};

// final(C++11): 이 클래스는 더 상속할 수 없다.
class Thermometer final : public Sensor
{
public:
    explicit Thermometer(std::string id) : Sensor(std::move(id)) {}
    void measure(double raw) { storeRaw(raw); }
    double celsius() const { return lastRaw() - 0.4; }
};

int main()
{
    Thermometer kitchen("T-01");
    kitchen.measure(22.0);
    const Sensor& any = kitchen;
    std::cout << any.id() << ": " << kitchen.celsius() << '\n';
}
