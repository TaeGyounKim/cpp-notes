#include <algorithm>
#include <cstddef>
#include <print>
#include <string>
#include <utility>
#include <vector>

class Grid
{
public:
    Grid() = default;
    Grid(std::string name, std::size_t width, std::size_t height)
        : m_name{ std::move(name) }, m_width{ width }, m_height{ height },
          m_cells{ new double[width * height]{} }
    {
        std::println("  일반 생성자 ({})", m_name);
    }
    ~Grid() { delete[] m_cells; }   // cleanup()은 소멸자로 들어왔다.

    Grid(const Grid& src) : Grid{ src.m_name, src.m_width, src.m_height }
    {
        std::println("  복사 생성자");
        std::copy(src.m_cells, src.m_cells + m_width * m_height, m_cells);
    }
    Grid& operator=(const Grid& rhs)
    {
        std::println("  복사 대입");
        Grid temp{ rhs };            // 복사 후 교환
        swap(temp);
        return *this;
    }

    // 이동 생성자: 빈 *this와 원본을 맞바꾼다.
    Grid(Grid&& src) noexcept
    {
        std::println("  이동 생성자");
        swap(src);
    }
    // 이동 대입: 이동 후 교환
    Grid& operator=(Grid&& rhs) noexcept
    {
        std::println("  이동 대입");
        auto moved{ std::move(rhs) };   // rhs를 moved로 옮긴다(noexcept).
        swap(moved);                    // 예외 없는 연산으로 확정
        return *this;
    }                                   // moved가 원래 내용을 정리한다.

    // 멤버를 추가하면 여기만 고치면 된다.
    void swap(Grid& other) noexcept
    {
        std::swap(m_name, other.m_name);
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_cells, other.m_cells);
    }

private:
    std::string m_name;
    std::size_t m_width{ 0 };
    std::size_t m_height{ 0 };
    double* m_cells{ nullptr };
};

Grid makeGrid()
{
    return Grid{ "임시", 3, 2 };
}

int main()
{
    std::vector<Grid> grids;
    for (int i{ 0 }; i < 2; ++i) {
        std::println("반복 {} (capacity {})", i, grids.capacity());
        grids.push_back(Grid{ "큰 격자", 100, 100 });
    }

    std::println("s = makeGrid();");
    Grid s{ "s", 2, 3 };
    s = makeGrid();

    std::println("s2 = s;");
    Grid s2{ "s2", 5, 6 };
    s2 = s;
}
