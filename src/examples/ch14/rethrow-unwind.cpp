#include <exception>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>

// 소멸될 때 이름을 출력하는 자원
class Tracer
{
public:
    explicit Tracer(std::string name) : m_name{ std::move(name) }
    {
        std::println("  {} 확보", m_name);
    }
    ~Tracer() { std::println("  {} 정리", m_name); }

private:
    std::string m_name;
};

void inner()
{
    Tracer local{ "inner의 지역 객체" };
    throw std::invalid_argument{ "inner에서 던짐" };
    std::println("여기는 실행되지 않음");
}

void middle()
{
    Tracer onStack{ "middle의 지역 객체" };
    auto owned{ std::make_unique<Tracer>("middle의 unique_ptr") };
    Tracer* raw{ new Tracer{ "middle의 날 포인터" } };   // 누수된다!
    inner();
    delete raw;                                          // 도달하지 않음
}

void relay(bool sliced)
{
    try {
        inner();
    } catch (const std::exception& e) {
        std::println("  relay가 잡음: {}", e.what());
        if (sliced) { throw e; }   // 잘못: std::exception으로 잘린 사본
        throw;                     // 맞음: 원래 예외를 그대로
    }
}

int main()
{
    std::println("[스택 풀기]");
    try {
        middle();
    } catch (const std::exception& e) {
        std::println("main이 잡음: {}", e.what());
    }

    for (bool sliced : { false, true }) {
        std::println("[다시 던지기: {}]", sliced ? "throw e;" : "throw;");
        try {
            relay(sliced);
        } catch (const std::invalid_argument& e) {
            std::println("main: invalid_argument로 잡음");
        } catch (const std::exception& e) {
            std::println("main: exception으로 잡음(잘림)");
        }
    }
}
