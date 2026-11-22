#include <iostream>

class Device
{
public:
    virtual ~Device() {}
    virtual void beep(int times = 1)
    {
        std::cout << "Device " << times << '\n';
    }
};

class Sensor : public Device
{
public:
    void beep(int times = 3) override
    {
        std::cout << "Sensor " << times << '\n';
    }
};

int main()
{
    Sensor sensor;
    Device& ref = sensor;
    sensor.beep();   // Sensor 3
    ref.beep();      // Sensor 1: 기본 인수는 Device 쪽 값
}
