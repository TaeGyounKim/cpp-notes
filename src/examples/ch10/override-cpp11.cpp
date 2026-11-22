#include <iostream>
#include <string>

class Sensor
{
public:
    virtual ~Sensor() {}
    virtual std::string describe() const { return "일반 센서"; }
};

class Thermometer : public Sensor
{
public:
    // override는 C++11부터. 그 이전에는 virtual만 다시 적었다.
    std::string describe() const override { return "온도계"; }
};

void report(const Sensor& sensor)
{
    std::cout << sensor.describe() << '\n';
}

int main()
{
    Thermometer kitchen;
    report(kitchen);
}
