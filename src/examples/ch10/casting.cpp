#include <print>
#include <typeinfo>

class Device
{
public:
    virtual ~Device() = default;   // dynamic_cast에는 가상 함수가 필요하다.
};

class Thermometer : public Device
{
public:
    double celsius() const { return 21.5; }
};

class Camera : public Device {};

void inspect(Device* device)
{
    // 다운캐스트: 실제로 Thermometer일 때만 성공한다.
    if (auto* t{ dynamic_cast<Thermometer*>(device) }; t != nullptr) {
        std::println("  온도계: {}°C", t->celsius());
    } else {
        std::println("  온도계 아님(nullptr)");
    }
}

int main()
{
    Thermometer thermo;
    Camera camera;

    Device& asDevice{ thermo };   // 업캐스트: 참조로. 슬라이싱 없음
    inspect(&thermo);
    inspect(&camera);

    try {
        auto& t{ dynamic_cast<Thermometer&>(static_cast<Device&>(camera)) };
        std::println("{}", t.celsius());
    } catch (const std::bad_cast&) {
        std::println("  참조 다운캐스트 실패: std::bad_cast");
    }
    std::println("asDevice는 온도계? {}",
                 dynamic_cast<Thermometer*>(&asDevice) != nullptr);
}
