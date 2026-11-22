#include <bit>
#include <cstdint>
#include <print>

class Device
{
public:
    virtual ~Device() = default;
};

class Thermometer : public Device
{
public:
    double celsius() const { return 21.5; }
};

// 받은 포인터가 실제로 무엇을 가리키는지 컴파일러는 모른다.
Thermometer* asThermometer(Device* device)
{
    return dynamic_cast<Thermometer*>(device);   // 실행 중 검사
}

int main()
{
    // static_cast: 언어가 허용하는 변환을 드러내 적는다.
    int sum{ 7 };
    int count{ 2 };
    std::println("평균: {}", static_cast<double>(sum) / count);   // 3.5

    // 계층 안에서 위로는 캐스트가 필요 없고, 아래로는 static_cast로 된다.
    Thermometer thermo;
    Device* device{ &thermo };                            // 업캐스트
    auto* t1{ static_cast<Thermometer*>(device) };   // 검사 없는 다운캐스트
    auto* t2{ asThermometer(device) };               // 검사하는 다운캐스트
    std::println("static_cast: {}, dynamic_cast: {}", t1->celsius(),
                 t2 != nullptr);

    Device plain;
    auto* t3{ asThermometer(&plain) };   // 실제로는 Device
    std::println("Device를 Thermometer로: {}", t3 == nullptr ? "nullptr" : "?");
    // static_cast<Thermometer*>(&plain)도 컴파일은 되지만 그 포인터로
    // celsius()를 부르면 정의되지 않은 동작이다.

    // void*와 오가기: void*로는 암시적으로, 돌아올 때는 static_cast
    void* raw{ &thermo };
    auto* back{ static_cast<Thermometer*>(raw) };
    std::println("void*에서 돌아옴: {}", back->celsius());

    // 포인터를 정수로: reinterpret_cast. 충분히 큰 정수 타입이어야 한다.
    auto address{ reinterpret_cast<std::uintptr_t>(&thermo) };
    std::println("주소를 정수로 바꿈: {}", address != 0);

    // bit_cast: 비트를 그대로 다른 타입으로 해석한다(크기가 같아야 함).
    float value{ 1.5f };
    auto bits{ std::bit_cast<std::uint32_t>(value) };
    std::println("1.5f의 비트: {:#010x}", bits);
    std::println("되돌리기: {}", std::bit_cast<float>(bits));
}
