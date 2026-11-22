#include <print>

class Device
{
public:
    virtual ~Device() = default;
    virtual void beep(int times = 1) { std::println("  Device: {}번", times); }

protected:
    virtual void secret() { std::println("  Device: 비밀 설정"); }
};

class Sensor : public Device
{
public:
    void beep(int times = 3) override { std::println("  Sensor: {}번", times); }
    using Device::secret;   // protected였던 secret()을 public으로 연다.
};

int main()
{
    Sensor sensor;
    Device& ref{ sensor };

    std::println("기본 인수는 컴파일 시점의 타입을 따른다");
    sensor.beep();   // Sensor판, 기본값 3
    ref.beep();      // Sensor판이 불리지만 기본값은 Device의 1

    std::println("접근 지정 바꾸기");
    sensor.secret();   // Sensor로는 부를 수 있다.
    // ref.secret();   // 컴파일 오류: Device에서는 여전히 protected
}
