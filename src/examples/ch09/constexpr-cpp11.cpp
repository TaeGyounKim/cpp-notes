#include <iostream>

// C++11의 constexpr 함수는 return 문 하나만 가질 수 있다.
// 그래서 조건은 ?:로, 반복은 재귀로 쓴다.
constexpr int slotsPerDay(int minutesPerSlot)
{
    return minutesPerSlot <= 0 ? 0 : 24 * 60 / minutesPerSlot;
}

constexpr unsigned power(unsigned base, unsigned exp)
{
    return exp == 0 ? 1 : base * power(base, exp - 1);
}

class GridSize
{
public:
    constexpr GridSize(unsigned w, unsigned h) : m_width(w), m_height(h) {}
    constexpr unsigned cells() const { return m_width * m_height; }

private:
    unsigned m_width;
    unsigned m_height;
};

int main()
{
    int readings[slotsPerDay(30)] = {};
    constexpr GridSize room(8, 2);
    int cells[room.cells()] = {};
    static_assert(power(2, 10) == 1024, "컴파일 중에 확인");
    std::cout << sizeof(readings) / sizeof(readings[0]) << ' '
              << sizeof(cells) / sizeof(cells[0]) << '\n';
}
