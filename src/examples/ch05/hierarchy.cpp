#include <algorithm>
#include <memory>
#include <print>
#include <string>
#include <utility>
#include <vector>

// 맨 위: 모든 기기에 공통인 것
class Device
{
public:
    explicit Device(std::string name) : m_name{ std::move(name) } {}
    virtual ~Device() = default;

    const std::string& getName() const { return m_name; }
    virtual void report() const { std::println("{}: 연결됨", m_name); }

private:
    std::string m_name;
};

// 중간: 조명과 선풍기를 만들다 보니 "0~100 단계 조절" 코드가 똑같았다.
// 공통 부모로 끌어올린다.
class AdjustableDevice : public Device
{
public:
    using Device::Device;   // Device의 생성자를 그대로 쓴다.

    void setLevel(int level) { m_level = std::clamp(level, 0, 100); }
    int getLevel() const { return m_level; }

private:
    int m_level{ 0 };
};

class Light : public AdjustableDevice
{
public:
    using AdjustableDevice::AdjustableDevice;
    void report() const override
    {
        std::println("{}: 밝기 {}%", getName(), getLevel());
    }
};

class Fan : public AdjustableDevice
{
public:
    using AdjustableDevice::AdjustableDevice;
    void report() const override
    {
        std::println("{}: 풍량 {}%", getName(), getLevel());
    }
};

// 문 잠금장치는 단계 조절이 없다. Device에서 바로 내려온다.
class DoorLock : public Device
{
public:
    using Device::Device;
    void lock() { m_isLocked = true; }
    void report() const override
    {
        std::println("{}: {}", getName(), m_isLocked ? "잠김" : "열림");
    }

private:
    bool m_isLocked{ false };
};

int main()
{
    auto light{ std::make_unique<Light>("거실 조명") };
    light->setLevel(70);
    auto fan{ std::make_unique<Fan>("안방 선풍기") };
    fan->setLevel(150);   // 범위 검사는 AdjustableDevice가 한 번만 한다.
    auto lock{ std::make_unique<DoorLock>("현관") };
    lock->lock();

    std::vector<std::unique_ptr<Device>> devices;
    devices.push_back(std::move(light));
    devices.push_back(std::move(fan));
    devices.push_back(std::move(lock));

    for (const auto& device : devices) {
        device->report();
    }
}
