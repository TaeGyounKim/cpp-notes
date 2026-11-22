#include <algorithm>
#include <print>
#include <string>
#include <utility>

// 배터리: 한 가지 일(충전량 관리)만 맡는다. 어느 기기에도 들어갈 수 있다.
class Battery
{
public:
    explicit Battery(int capacity) : m_capacity{ capacity } {}

    // 쓸 수 있었던 만큼만 쓰고, 실제로 쓴 양을 돌려준다.
    int drain(int amount)
    {
        const int used{ std::min(amount, m_charge) };
        m_charge -= used;
        return used;
    }
    void charge() { m_charge = m_capacity; }
    int getPercent() const { return m_charge * 100 / m_capacity; }

private:
    int m_capacity;
    int m_charge{ m_capacity };
};

// 드론은 배터리를 가진다. 배터리의 규칙은 몰라도 된다.
class Drone
{
public:
    explicit Drone(std::string name) : m_name{ std::move(name) } {}

    void fly(int minutes)
    {
        const int used{ m_battery.drain(minutes * 30) };
        std::println("{}: {}분 비행 (배터리 {}%)", m_name, used / 30,
                     m_battery.getPercent());
    }

private:
    std::string m_name;
    Battery m_battery{ 1200 };
};

// 같은 Battery를 전혀 다른 기기에서 그대로 다시 쓴다.
class Flashlight
{
public:
    void shine(int minutes)
    {
        m_battery.drain(minutes);
        std::println("손전등: {}분 켬 (배터리 {}%)", minutes,
                     m_battery.getPercent());
    }

private:
    Battery m_battery{ 300 };
};

int main()
{
    Drone drone{ "drone-1" };
    drone.fly(10);
    drone.fly(50);   // 남은 만큼만 난다.

    Flashlight flashlight;
    flashlight.shine(60);
}
