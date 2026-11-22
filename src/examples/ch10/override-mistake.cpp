#include <print>

class Sensor
{
public:
    virtual ~Sensor() = default;
    virtual void calibrate(double offset)
    {
        std::println("  Sensor::calibrate({})", offset);
    }
};

class Thermometer : public Sensor
{
public:
    // 실수: 매개변수가 int라서 재정의가 아니라 새 가상 함수가 된다.
    virtual void calibrate(int offset)
    {
        std::println("  Thermometer::calibrate({})", offset);
    }
    // void calibrate(int offset) override { }  // override면 오류로 잡힘
};

int main()
{
    Thermometer kitchen;
    Sensor& ref{ kitchen };
    std::println("ref.calibrate(-0.4)");
    ref.calibrate(-0.4);   // Thermometer판이 불릴 줄 알았지만...
}
