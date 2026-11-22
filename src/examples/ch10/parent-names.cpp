#include <print>
#include <string>

class Device
{
public:
    virtual ~Device() = default;
    virtual std::string describe() const { return "장치"; }
    virtual int weightGrams() const { return 400; }
};

class Sensor : public Device
{
public:
    std::string describe() const override
    {
        return "센서 " + Device::describe();   // 부모의 판을 부르고 덧붙인다.
    }
};

class Thermometer : public Sensor
{
public:
    std::string describe() const override
    {
        return "온도 " + Sensor::describe();
    }
    // Sensor는 weightGrams()를 재정의하지 않았다. 위로 올라가 Device판을 쓴다.
    int weightGrams() const override { return Sensor::weightGrams() / 2; }
};

class Camera : public Device
{
public:
    std::string describe() const override
    {
        return "카메라 " + Device::describe();
    }
};

int main()
{
    Thermometer t;
    Camera c;
    std::println("{} / {}g", t.describe(), t.weightGrams());
    std::println("{} / {}g", c.describe(), c.weightGrams());
}
