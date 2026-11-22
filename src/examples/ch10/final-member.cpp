#include <print>
#include <string>

class Sensor
{
public:
    virtual ~Sensor() = default;
    virtual std::string unit() const { return "?"; }
};

class Thermometer : public Sensor
{
public:
    // 이 아래로는 더 재정의하지 못하게 막는다.
    std::string unit() const override final { return "°C"; }
};

class KitchenThermometer : public Thermometer
{
public:
    // std::string unit() const override { return "°F"; }   // 컴파일 오류
};

int main()
{
    KitchenThermometer k;
    const Sensor& s{ k };
    std::println("단위: {}", s.unit());
}
