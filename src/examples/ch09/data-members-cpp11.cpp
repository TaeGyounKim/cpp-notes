#include <algorithm>
#include <cstddef>
#include <iostream>

class Grid
{
public:
    static constexpr std::size_t MaxWidth = 100;   // 클래스 안 초기화 가능

    explicit Grid(std::size_t width)
        : m_id(ms_counter++), m_width(std::min(width, MaxWidth))
    {
    }
    std::size_t id() const { return m_id; }
    std::size_t width() const { return m_width; }

private:
    static std::size_t ms_counter;   // inline 변수(C++17)가 없으므로 선언만
    const std::size_t m_id;
    std::size_t m_width;
};

// C++17 이전: static 데이터 멤버는 클래스 밖(구현 파일)에서 정의한다.
std::size_t Grid::ms_counter = 0;
// std::min은 참조로 받으므로 MaxWidth의 정의도 필요하다(C++17부터는 불필요).
constexpr std::size_t Grid::MaxWidth;

int main()
{
    Grid a(3);
    Grid b(500);
    std::cout << a.id() << ':' << a.width() << ' '
              << b.id() << ':' << b.width() << '\n';
}
