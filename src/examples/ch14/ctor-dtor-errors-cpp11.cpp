#include <iostream>
#include <stdexcept>
#include <utility>

// 함수 try 블록은 C++98부터, 소멸자가 기본으로 noexcept인 것은 C++11부터다.
class Gauge
{
public:
    explicit Gauge(int) { throw std::runtime_error("게이지 초기화 실패"); }
};

class Panel
{
public:
    Panel()
    try : m_gauge(42)
    {
    }
    catch (const std::exception& e)
    {
        std::cout << "  함수 try 블록이 잡음: " << e.what() << '\n';
    }

private:
    Gauge m_gauge;
};

struct Plain { ~Plain() {} };

int main()
{
    try {
        Panel p;
    } catch (const std::exception& e) {
        std::cout << "main: " << e.what() << '\n';
    }
    std::cout << std::boolalpha
              << noexcept(std::declval<Plain&>().~Plain()) << '\n';
}
