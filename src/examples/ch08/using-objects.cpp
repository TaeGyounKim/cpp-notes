#include <memory>
#include <print>

class Temperature
{
public:
    void setCelsius(double celsius) { m_celsius = celsius; }
    double getCelsius() const { return m_celsius; }

private:
    double m_celsius{ 0.0 };
};

int main()
{
    // 스택의 객체: 보통 변수처럼 선언하고 .으로 멤버를 쓴다.
    Temperature inside;
    Temperature outside;
    inside.setCelsius(22.0);
    outside.setCelsius(-3.5);
    std::println("스택: {} / {}", inside.getCelsius(), outside.getCelsius());

    // 자유 저장소의 객체: 포인터로 다루고 ->로 멤버를 쓴다.
    Temperature* fridge{ new Temperature{} };
    fridge->setCelsius(4.0);
    std::println("자유 저장소: {}", fridge->getCelsius());
    std::println("같은 뜻: {}", (*fridge).getCelsius());   // 역참조 후 .
    delete fridge;
    fridge = nullptr;

    // 권장: 스마트 포인터. delete를 적지 않는다.
    auto freezer{ std::make_unique<Temperature>() };
    freezer->setCelsius(-18.0);
    std::println("스마트 포인터: {}", freezer->getCelsius());
}
