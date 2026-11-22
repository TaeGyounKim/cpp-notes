#include <algorithm>
#include <cstddef>
#include <print>
#include <utility>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height },
          m_cells{ new double[width * height]{} }
    {
    }
    ~Grid() { cleanup(); }

    // 복사(앞 글): 깊은 복사, 복사 후 교환
    Grid(const Grid& src) : Grid{ src.m_width, src.m_height }
    {
        std::println("  [복사 생성자]");
        std::copy(src.m_cells, src.m_cells + size(), m_cells);
    }
    Grid& operator=(const Grid& rhs)
    {
        std::println("  [복사 대입]");
        Grid temp{ rhs };
        swap(temp);
        return *this;
    }

    // 이동 생성자: 원본의 배열을 그대로 넘겨받는다.
    Grid(Grid&& src) noexcept
    {
        std::println("  [이동 생성자]");
        moveFrom(src);
    }

    // 이동 대입 연산자: 내 배열을 정리하고 원본의 배열을 넘겨받는다.
    Grid& operator=(Grid&& rhs) noexcept
    {
        std::println("  [이동 대입]");
        if (this == &rhs) {   // a = std::move(a); 대비
            return *this;
        }
        cleanup();
        moveFrom(rhs);
        return *this;
    }

    void swap(Grid& other) noexcept
    {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_cells, other.m_cells);
    }

    void report(const char* name) const
    {
        std::println("    {}: {}x{}, 배열 {}", name, m_width, m_height,
                     m_cells ? "있음" : "없음");
    }

private:
    std::size_t size() const { return m_width * m_height; }

    void cleanup() noexcept
    {
        delete[] m_cells;
        m_cells = nullptr;
        m_width = m_height = 0;
    }

    // 얕게 가져오고, 원본은 빈 상태로 만든다(소유권 이전).
    void moveFrom(Grid& src) noexcept
    {
        m_width = std::exchange(src.m_width, 0);
        m_height = std::exchange(src.m_height, 0);
        m_cells = std::exchange(src.m_cells, nullptr);
    }

    std::size_t m_width{ 0 };
    std::size_t m_height{ 0 };
    double* m_cells{ nullptr };
};

int main()
{
    Grid a{ 4, 3 };

    std::println("Grid b{{ a }};");
    Grid b{ a };
    std::println("Grid c{{ std::move(a) }};");
    Grid c{ std::move(a) };
    a.report("a");
    c.report("c");

    std::println("b = Grid{{ 2, 2 }};");
    b = Grid{ 2, 2 };   // 임시 객체(우측값)라서 이동 대입
    b.report("b");

    std::println("c = std::move(c);");
    c = std::move(c);   // 자기 이동: 확인이 없으면 배열을 잃는다.
    c.report("c");
}
