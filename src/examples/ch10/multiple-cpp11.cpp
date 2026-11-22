#include <iostream>

class Camera
{
public:
    virtual ~Camera() {}
    virtual void start() { std::cout << "카메라 앱 시작\n"; }
};

class Player
{
public:
    virtual ~Player() {}
    virtual void start() { std::cout << "플레이어 앱 시작\n"; }
};

class Phone : public Camera, public Player
{
public:
    void start() override { Player::start(); }   // override: C++11
};

int main()
{
    Phone phone;
    phone.start();
    phone.Camera::start();
}
