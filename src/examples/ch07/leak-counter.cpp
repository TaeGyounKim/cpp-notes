#include <print>

// 살아 있는 객체 수를 세는 클래스
class Tracked
{
public:
    Tracked() { ++s_alive; }
    ~Tracked() { --s_alive; }
    static int alive() { return s_alive; }

private:
    static inline int s_alive{ 0 };
};

void leaky()
{
    new Tracked{};   // 버그: 돌려받은 주소를 버렸다. 해제할 방법이 없다.
}

void careful()
{
    Tracked* tracked{ new Tracked{} };
    // ... tracked를 쓴다 ...
    delete tracked;   // new 하나에 delete 하나
    tracked = nullptr;
}

int main()
{
    for (int i{ 0 }; i < 3; ++i) {
        careful();
    }
    std::println("careful 세 번 뒤 남은 객체: {}", Tracked::alive());

    for (int i{ 0 }; i < 3; ++i) {
        leaky();
    }
    std::println("leaky 세 번 뒤 남은 객체: {}", Tracked::alive());
}
