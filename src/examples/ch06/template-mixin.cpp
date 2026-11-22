#include <print>
#include <string>
#include <utility>

class Vehicle
{
public:
    explicit Vehicle(std::string id) : m_id{ std::move(id) } {}
    const std::string& getId() const { return m_id; }

private:
    std::string m_id;
};

class Bicycle : public Vehicle
{
public:
    using Vehicle::Vehicle;
    int getWheelCount() const { return 2; }
};

class Scooter : public Vehicle
{
public:
    using Vehicle::Vehicle;
    int getMaxSpeed() const { return 25; }
};

// "대여할 수 있다"는 개념. 어떤 탈것에든 덧붙일 수 있다.
// T 자리에 들어온 클래스를 물려받는 클래스 템플릿이다.
template <typename T>
class Rentable : public T
{
public:
    using T::T;   // T의 생성자를 그대로 쓴다.

    void rentTo(std::string customer)
    {
        m_customer = std::move(customer);
        std::println("{} → {} 대여", this->getId(), m_customer);
    }
    bool isRented() const { return !m_customer.empty(); }

private:
    std::string m_customer;
};

int main()
{
    // 대여하지 않는 탈것: 대여 기능의 비용이 없다.
    Bicycle myBike{ "my-bike" };
    std::println("{}: 바퀴 {}개", myBike.getId(), myBike.getWheelCount());

    // 대여용 탈것: 원래 기능에 대여 기능이 더해진다.
    Rentable<Bicycle> shareBike{ "B-102" };
    Rentable<Scooter> shareScooter{ "S-007" };
    shareBike.rentTo("Kim");
    shareScooter.rentTo("Lee");
    std::println("{}: 바퀴 {}개, 대여 중 {}", shareBike.getId(),
                 shareBike.getWheelCount(), shareBike.isRented());
    std::println("{}: 최고 {}km/h", shareScooter.getId(),
                 shareScooter.getMaxSpeed());
}
