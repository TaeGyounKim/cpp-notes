#include <print>
#include <string>
#include <utility>

class Device
{
public:
    virtual ~Device() = default;
    explicit Device(std::string name) : m_name{ std::move(name) } {}
    Device(const Device& src) : m_name{ src.m_name }
    {
        std::println("  Device 복사 생성자");
    }
    Device& operator=(const Device& rhs)
    {
        std::println("  Device 대입 연산자");
        m_name = rhs.m_name;
        return *this;
    }
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

class Sensor : public Device
{
public:
    Sensor(std::string name, int channel)
        : Device{ std::move(name) }, m_channel{ channel } {}

    // 복사 연산을 직접 쓰면 기반 클래스의 것을 직접 불러야 한다.
    Sensor(const Sensor& src) : Device{ src }, m_channel{ src.m_channel }
    {
        std::println("  Sensor 복사 생성자");
    }
    Sensor& operator=(const Sensor& rhs)
    {
        if (this == &rhs) { return *this; }
        Device::operator=(rhs);   // 기반 클래스 부분을 대입
        m_channel = rhs.m_channel;
        std::println("  Sensor 대입 연산자");
        return *this;
    }
    int channel() const { return m_channel; }

private:
    int m_channel;
};

int main()
{
    Sensor a{ "부엌", 1 };
    std::println("Sensor b{{ a }};");
    Sensor b{ a };
    Sensor c{ "거실", 2 };
    std::println("c = a;");
    c = a;
    std::println("c: {} 채널 {}", c.name(), c.channel());
}
