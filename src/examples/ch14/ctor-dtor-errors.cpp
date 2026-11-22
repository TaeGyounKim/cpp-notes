#include <exception>
#include <memory>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>

class Part
{
public:
    explicit Part(int id) : m_id{ id }
    {
        if (id == 3) { throw std::runtime_error{ "부품 3 생성 실패" }; }
        std::println("  부품 {} 생성", m_id);
    }
    ~Part() { std::println("  부품 {} 소멸", m_id); }

private:
    int m_id;
};

// 생성자에서 예외가 나가면 이 객체의 소멸자는 불리지 않는다.
// 그러나 이미 다 만들어진 멤버(여기서는 vector 안의 부품들)는 정리된다.
class Machine
{
public:
    explicit Machine(int count)
    {
        for (int i{ 1 }; i <= count; ++i) {
            m_parts.push_back(std::make_unique<Part>(i));
        }
    }
    ~Machine() { std::println("  Machine 소멸자"); }   // 불리지 않음

private:
    std::vector<std::unique_ptr<Part>> m_parts;
};

class Gauge
{
public:
    explicit Gauge(int) { throw std::runtime_error{ "게이지 초기화 실패" }; }
};

// 함수 try 블록: 생성자 초기화 목록에서 나는 예외도 잡는다.
class Panel
{
public:
    Panel()
    try : m_gauge{ 42 }
    {
    }
    catch (const std::exception& e)
    {
        std::println("  함수 try 블록이 잡음: {}", e.what());
        // 아무것도 던지지 않으면 잡은 예외가 자동으로 다시 던져진다.
    }

private:
    Gauge m_gauge;
};

int main()
{
    std::println("[Machine 5개 부품]");
    try {
        Machine m{ 5 };
    } catch (const std::exception& e) {
        std::println("main: {}", e.what());
    }

    std::println("[Panel]");
    try {
        Panel p;
    } catch (const std::exception& e) {
        std::println("main: {}", e.what());
    }

    // 소멸자는 기본으로 noexcept다.
    std::println("~Part()는 noexcept? {}",
                 noexcept(std::declval<Part&>().~Part()));
}
