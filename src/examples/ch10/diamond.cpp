#include <print>

// 맨 위 클래스를 순수 가상 함수만 가진 추상 클래스로 둔다.
class Device
{
public:
    virtual ~Device() = default;
    virtual void sleep() = 0;
};

class Camera : public Device
{
public:
    void sleep() override { std::println("  카메라 렌즈 닫음"); }
};

class Player : public Device
{
public:
    void sleep() override { std::println("  재생 멈춤"); }
};

class Phone : public Camera, public Player
{
public:
    using Player::sleep;   // Player판 sleep()을 쓰겠다고 밝힌다.
};

int main()
{
    Phone phone;
    phone.sleep();           // Player::sleep
    phone.Camera::sleep();   // 원하면 다른 쪽도 지정해 부를 수 있다.
}
