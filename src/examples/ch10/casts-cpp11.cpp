#include <cstdint>
#include <cstring>
#include <iostream>

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

int main()
{
    Thermometer thermo;
    Device* device = &thermo;
    Thermometer* t = dynamic_cast<Thermometer*>(device);
    std::cout << t->celsius() << '\n';

    // std::bit_cast(C++20) 대신 memcpy로 비트를 복사한다.
    float value = 1.5f;
    std::uint32_t bits;
    static_assert(sizeof(bits) == sizeof(value), "크기가 같아야 함");
    std::memcpy(&bits, &value, sizeof(bits));
    std::cout << std::hex << "0x" << bits << '\n';
}
