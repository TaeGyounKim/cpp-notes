#include <print>

class Counter
{
    int m_count{ 0 };   // 첫 접근 지정자 앞: class에서는 private

public:
    void increase() { ++m_count; }
    int get() const { return m_count; }
};

// struct는 기본이 public. 데이터만 모을 때 주로 쓴다.
struct Point
{
    double x;
    double y;
};

int main()
{
    Counter counter;
    counter.increase();
    counter.increase();
    std::println("count: {}", counter.get());
    // counter.m_count = 100;   // 컴파일 오류: private 멤버

    Point p{ 3.0, 4.0 };
    p.x = 5.0;   // public이므로 바로 바꿀 수 있다.
    std::println("({}, {})", p.x, p.y);
}
