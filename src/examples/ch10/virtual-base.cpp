#include <print>
#include <string>
#include <utility>

class Device
{
public:
    explicit Device(double watts) : m_watts{ watts } {}
    virtual ~Device() = default;
    double watts() const { return m_watts; }
    virtual void sleep() { std::println("  절전 모드"); }   // 구현이 있는 함수

protected:
    // 가장 아래 클래스가 Device를 직접 만들지 않을 때 쓰인다.
    Device() = default;

private:
    double m_watts{ 0.0 };
};

// 가상 기반 클래스: Phone 안에 Device 부분이 하나만 생긴다.
class Camera : public virtual Device
{
public:
    Camera(double watts, std::string lens)
        : Device{ watts }, m_lens{ std::move(lens) } {}

protected:
    explicit Camera(std::string lens) : m_lens{ std::move(lens) } {}

private:
    std::string m_lens;
};

class Player : public virtual Device
{
public:
    Player(double watts, int volume) : Device{ watts }, m_volume{ volume } {}

protected:
    explicit Player(int volume) : m_volume{ volume } {}

private:
    int m_volume;
};

class WrongPhone : public Camera, public Player
{
public:
    // Camera와 Player에게 Device 생성을 맡겼지만 무시된다.
    WrongPhone(double watts)
        : Camera{ watts, "광각" }, Player{ watts, 5 } {}
};

class Phone : public Camera, public Player
{
public:
    // 가장 아래 클래스가 가상 기반 클래스를 직접 만든다.
    Phone(double watts)
        : Device{ watts }, Camera{ "광각" }, Player{ 5 } {}
};

int main()
{
    Phone phone{ 4.5 };
    phone.sleep();   // Device 부분이 하나뿐이라 모호하지 않다.
    std::println("Phone: {}W", phone.watts());

    WrongPhone wrong{ 4.5 };
    std::println("WrongPhone: {}W  <- Device의 기본 생성자가 쓰였다",
                 wrong.watts());
}
