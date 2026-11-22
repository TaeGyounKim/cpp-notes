#include <print>
#include <string>
#include <string_view>

class Device
{
public:
    virtual ~Device() = default;
    Device() = default;
    explicit Device(std::string_view name) : m_name{ name } {}
    explicit Device(int serial) : m_name{ "#" + std::to_string(serial) } {}
    const std::string& name() const { return m_name; }

    virtual void describe() const { std::println("  장치 {}", m_name); }

private:
    std::string m_name{ "이름 없음" };
};

class Sensor : public Device
{
public:
    using Device::Device;   // Device의 생성자를 모두 물려받는다.

    // int를 받는 생성자는 직접 정의: 물려받은 것을 감춘다.
    explicit Sensor(int serial) : Device{ serial }, m_channel{ serial % 4 } {}

    using Device::describe;   // 기반 클래스의 describe()도 계속 쓰고
    virtual void describe(bool verbose) const   // 새 오버로드를 더한다.
    {
        std::println("  센서 {} (채널 {}){}", name(), m_channel,
                     verbose ? " 자세히" : "");
    }

private:
    int m_channel{ 0 };   // 물려받은 생성자로 만들어도 0으로 초기화된다.
};

int main()
{
    Sensor a;               // 물려받은 기본 생성자
    Sensor b{ "부엌" };     // 물려받은 string_view 생성자
    Sensor c{ 1002 };       // Sensor가 직접 정의한 int 생성자
    a.describe();
    b.describe(true);
    c.describe(false);
}
