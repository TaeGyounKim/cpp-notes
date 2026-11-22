#include <print>

class Counter
{
public:
    int value() { return 5; }
};

int value() { return 10; }       // 전역 범위

namespace settings
{
    int value() { return 20; }
}

int main()
{
    Counter counter;
    std::println("{}", counter.value());    // Counter 클래스의 value
    std::println("{}", settings::value());  // settings 네임스페이스의 value
    std::println("{}", ::value());          // 전역 범위의 value
    std::println("{}", value());            // 가까운 범위부터 찾아 전역의 value

    // 안쪽 범위의 이름이 바깥 범위의 같은 이름을 가린다.
    int number{ 1 };
    {
        int number{ 2 };
        std::println("{}", number);         // 안쪽의 number
    }
    std::println("{}", number);             // 바깥쪽의 number
}
