#include <array>
#include <print>

class GridSize
{
public:
    GridSize() = default;   // 컴파일러가 만든 것은 저절로 constexpr
    constexpr GridSize(unsigned width, unsigned height)
        : m_width{ width }, m_height{ height }
    {
    }
    constexpr unsigned cells() const { return m_width * m_height; }

private:
    unsigned m_width{ 0 };
    unsigned m_height{ 0 };
};

int main()
{
    constexpr GridSize room{ 8, 2 };   // 컴파일 중에 만들어지는 객체
    constexpr GridSize empty;

    // 컴파일 중에 계산한 칸 수로 배열 크기를 정한다.
    std::array<double, room.cells()> cells{};
    std::println("칸 수: {}, 빈 격자: {}", cells.size(), empty.cells());
}
