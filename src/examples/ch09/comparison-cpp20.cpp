#include <compare>
#include <print>

class Reading
{
public:
    Reading(double value) : m_value{ value } {}
    double value() const { return m_value; }

    // C++20: ==와 <=> 두 개만 멤버로 쓰면 여섯 비교 연산자가 모두 된다.
    [[nodiscard]] bool operator==(const Reading& rhs) const
    {
        return m_value == rhs.m_value;
    }
    [[nodiscard]] std::partial_ordering operator<=>(const Reading& rhs) const
    {
        return m_value <=> rhs.m_value;   // double은 부분 순서
    }

private:
    double m_value;
};

// 데이터 멤버를 차례로 비교하면 되는 경우: 컴파일러에게 맡긴다.
struct Sample
{
    int hour;
    double celsius;
    [[nodiscard]] auto operator<=>(const Sample&) const = default;
    // <=>를 기본으로 정의하면 ==도 기본으로 함께 생긴다.
};

int main()
{
    Reading a{ 18.5 };
    Reading b{ 24.0 };
    std::println("a < b: {}, a >= b: {}, a != b: {}", a < b, a >= b, a != b);

    // 10 < a는 a > 10으로, 10 == a는 a == 10으로 바꿔 쓴다.
    std::println("10 < a: {}, 18.5 == a: {}", 10 < a, 18.5 == a);

    Sample s1{ 9, 18.5 };
    Sample s2{ 9, 21.0 };
    std::println("s1 < s2: {}, s1 == s2: {}", s1 < s2, s1 == s2);
}
