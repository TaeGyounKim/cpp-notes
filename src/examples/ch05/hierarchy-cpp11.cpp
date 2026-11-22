#include <algorithm>
#include <iostream>
#include <string>

class Device
{
public:
    explicit Device(std::string name) : m_name{ name } {}
    virtual ~Device() = default;
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
};

class AdjustableDevice : public Device
{
public:
    using Device::Device;   // 생성자 물려받기는 C++11부터 된다.

    void setLevel(int level)
    {
        // std::clamp(C++17) 대신 std::min과 std::max를 겹쳐 쓴다.
        m_level = std::min(std::max(level, 0), 100);
    }
    int getLevel() const { return m_level; }

private:
    int m_level{ 0 };
};

int main()
{
    AdjustableDevice fan{ "안방 선풍기" };
    fan.setLevel(150);
    std::cout << fan.getName() << ": " << fan.getLevel() << "%\n";
}
