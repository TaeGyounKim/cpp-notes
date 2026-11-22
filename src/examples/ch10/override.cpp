#include <print>
#include <string>

class Sensor
{
public:
    virtual ~Sensor() = default;   // 다음 글에서 설명

    virtual std::string describe() const { return "일반 센서"; }
    std::string kind() const { return "Sensor"; }   // virtual 아님
};

class Thermometer : public Sensor
{
public:
    std::string describe() const override { return "온도계"; }   // 재정의
    std::string kind() const { return "Thermometer"; }   // 감추기(재정의 아님)
};

void report(const Sensor& sensor)   // 기반 클래스 참조로 받는다.
{
    std::println("  describe(): {}, kind(): {}", sensor.describe(),
                 sensor.kind());
}

int main()
{
    Sensor plain;
    Thermometer kitchen;

    std::println("객체로 직접 부르기");
    std::println("  {} / {}", plain.describe(), kitchen.describe());

    std::println("Sensor 참조로 Sensor");
    report(plain);
    std::println("Sensor 참조로 Thermometer");
    report(kitchen);   // virtual인 describe()만 실제 타입을 따른다.

    std::println("Sensor 객체에 복사(슬라이싱)");
    Sensor copy{ kitchen };   // Thermometer 부분이 잘려 나간다.
    report(copy);
}
