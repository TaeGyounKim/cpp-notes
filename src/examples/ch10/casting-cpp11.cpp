#include <iostream>
#include <typeinfo>

class Device
{
public:
    virtual ~Device() {}
};

class Thermometer : public Device
{
public:
    double celsius() const { return 21.5; }
};

class Camera : public Device {};

void inspect(Device* device)
{
    // if 문 안의 초기화(C++17) 대신 바깥에서 변수를 선언한다.
    Thermometer* t = dynamic_cast<Thermometer*>(device);
    if (t != nullptr) {
        std::cout << "온도계: " << t->celsius() << '\n';
    } else {
        std::cout << "온도계 아님\n";
    }
}

int main()
{
    Thermometer thermo;
    Camera camera;
    inspect(&thermo);
    inspect(&camera);
}
