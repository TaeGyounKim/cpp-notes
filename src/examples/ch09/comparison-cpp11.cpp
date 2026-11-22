#include <iostream>

class Reading
{
public:
    Reading(double value) : m_value(value) {}
    double value() const { return m_value; }

private:
    double m_value;
};

// C++20 이전: 여섯 비교 연산자를 전역 함수로 모두 쓴다.
// ==와 <만 실제로 비교하고, 나머지는 그 둘로 만든다.
bool operator==(const Reading& lhs, const Reading& rhs)
{
    return lhs.value() == rhs.value();
}
bool operator<(const Reading& lhs, const Reading& rhs)
{
    return lhs.value() < rhs.value();
}
bool operator!=(const Reading& l, const Reading& r) { return !(l == r); }
bool operator>(const Reading& l, const Reading& r) { return r < l; }
bool operator<=(const Reading& l, const Reading& r) { return !(r < l); }
bool operator>=(const Reading& l, const Reading& r) { return !(l < r); }

int main()
{
    Reading a(18.5);
    Reading b(24.0);
    std::cout << std::boolalpha << (a < b) << ' ' << (a >= b) << ' '
              << (10 < a) << ' ' << (a != 18.5) << '\n';
}
