#include <iostream>
#include <typeinfo>

class Device
{
public:
    virtual ~Device() {}
    virtual void sleep() { std::cout << "절전 모드\n"; }
};

class Camera : public virtual Device {};   // 가상 기반 클래스: C++98부터
class Player : public virtual Device {};
class Phone : public Camera, public Player {};

int main()
{
    Phone phone;
    phone.sleep();
    Device& ref = phone;
    std::cout << std::boolalpha << (typeid(ref) == typeid(Phone)) << '\n';
}
