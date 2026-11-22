#include <print>
#include <string>
#include <utility>

class Probe
{
public:
    explicit Probe(std::string name) : m_name{ std::move(name) }
    {
        std::println("  + {} 생성", m_name);
    }

    // 소멸자: ~클래스이름. 반환 타입도 매개변수도 없다.
    ~Probe() { std::println("  - {} 소멸", m_name); }

    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

class Station
{
private:
    Probe m_inside{ "실내 센서" };    // 먼저 선언 -> 먼저 생성, 나중에 소멸
    Probe m_outside{ "실외 센서" };
};

int main()
{
    std::println("[블록 시작]");
    {
        Probe first{ "first" };
        Probe second{ "second" };
    }   // 닫는 중괄호: 선언의 역순으로 소멸
    std::println("[블록 끝]");

    std::println("[멤버 객체]");
    {
        Station station;
    }

    std::println("[자유 저장소]");
    Probe* kept{ new Probe{ "delete함" } };
    Probe* lost{ new Probe{ "delete 안 함" } };
    delete kept;   // 여기서 소멸자가 불린다.
    kept = nullptr;
    std::println("[main 끝] \"{}\" 객체는 아직 남아 있음", lost->name());
}   // lost는 소멸자가 불리지 않는다(메모리 누수).
