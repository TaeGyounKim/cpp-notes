#include <print>

class Device
{
public:
    virtual ~Device() = default;
    static void info() { std::println("  Device::info (static)"); }

    virtual void reset() { std::println("  Device::reset()"); }
    virtual void reset(int level)
    {
        std::println("  Device::reset({})", level);
    }
};

class Sensor : public Device
{
public:
    static void info() { std::println("  Sensor::info (static)"); }

    // 오버로드 하나만 재정의하면 나머지는 감춰진다. using으로 들여온다.
    using Device::reset;
    void reset() override { std::println("  Sensor::reset()"); }
};

int main()
{
    Sensor sensor;
    Device& ref{ sensor };

    std::println("static 멤버 함수: 컴파일 시점의 타입을 따른다");
    sensor.info();   // Sensor::info
    ref.info();      // Device::info (실제 객체와 무관)

    std::println("오버로드");
    sensor.reset();    // Sensor판
    sensor.reset(3);   // using 덕분에 Device판을 쓸 수 있다.
    ref.reset();       // 가상 함수: Sensor판
}
