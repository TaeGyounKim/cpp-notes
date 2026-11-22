#include <print>
#include <string>
#include <utility>

// 함수 객체: 호출 사이에 상태를 기억한다.
class RunningAverage
{
public:
    double operator()(double sample)   // 값을 넣고 지금까지의 평균을 돌려준다.
    {
        m_sum += sample;
        ++m_count;
        return m_sum / m_count;
    }
    // 매개변수가 다른 operator()를 더 둘 수 있다.
    double operator()() const { return m_count == 0 ? 0 : m_sum / m_count; }

private:
    double m_sum{ 0 };
    int m_count{ 0 };
};

// 데이터 멤버로 동작을 바꾸는 함수 객체
class Above
{
public:
    explicit Above(double limit) : m_limit{ limit } {}
    bool operator()(double value) const { return value > m_limit; }

private:
    double m_limit;
};

// C++23: this가 필요 없으면 static
struct Squarer
{
    static constexpr int operator()(int v) noexcept { return v * v; }
};

// 가장 단순한 스마트 포인터(설명용. 실제로는 std::unique_ptr를 쓴다)
template <typename T>
class Owner
{
public:
    explicit Owner(T* ptr) : m_ptr{ ptr } {}
    ~Owner() { delete m_ptr; }
    Owner(const Owner&) = delete;
    Owner& operator=(const Owner&) = delete;

    T& operator*() { return *m_ptr; }                // 가리키는 것의 참조
    const T& operator*() const { return *m_ptr; }
    T* operator->() { return m_ptr; }                // 포인터를 돌려준다.
    const T* operator->() const { return m_ptr; }

private:
    T* m_ptr{ nullptr };
};

int main()
{
    RunningAverage avg;
    for (double t : { 20.0, 22.0, 27.0 }) { std::println("평균 {}", avg(t)); }
    std::println("지금 평균 {}", avg());

    Above hot{ 25.0 };
    std::println("{} {}", hot(24.5), hot(26.0));

    int x{ Squarer{}(3) };
    auto fp{ &Squarer::operator() };   // static이라 보통 함수 포인터가 된다.
    std::println("{} {}", x, fp(x));

    Owner<int> n{ new int{ 5 } };
    *n += 1;                            // operator*가 참조를 돌려준다.
    Owner<std::string> s{ new std::string{ "센서" } };
    s->append("-7");                    // (s.operator->())->append("-7")
    std::println("{} {} {}", *n, *s, s->size());
}
