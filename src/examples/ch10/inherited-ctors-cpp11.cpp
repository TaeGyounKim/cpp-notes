#include <iostream>
#include <string>

class Device
{
public:
    virtual ~Device() {}
    explicit Device(const std::string& name) : m_name(name) {}
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

class Sensor : public Device
{
public:
    using Device::Device;   // 생성자 상속은 C++11부터

private:
    int m_channel = 0;      // 클래스 안 초기화도 C++11부터
};

int main()
{
    Sensor s(std::string("부엌"));
    std::cout << s.name() << '\n';
}
