#include <algorithm>
#include <cstddef>
#include <new>
#include <print>
#include <utility>

// 연습용 장치: 이 값이 true이면 다음 배열 할당이 실패한 것처럼 예외를 던진다.
bool g_failNextAllocation{ false };

double* allocate(std::size_t count)
{
    if (g_failNextAllocation) {
        g_failNextAllocation = false;
        throw std::bad_alloc{};
    }
    return new double[count]{};
}

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height },
          m_cells{ allocate(width * height) }
    {
    }
    Grid(const Grid& src) : Grid{ src.m_width, src.m_height }
    {
        std::copy(src.m_cells, src.m_cells + size(), m_cells);
    }
    ~Grid() { delete[] m_cells; }

    // 단순한 대입: 중간에 예외가 나면 객체가 망가진다.
    void assignNaive(const Grid& rhs)
    {
        if (this == &rhs) { return; }
        delete[] m_cells;
        m_cells = nullptr;
        m_width = rhs.m_width;
        m_height = rhs.m_height;
        m_cells = allocate(size());   // 여기서 예외가 나면?
        std::copy(rhs.m_cells, rhs.m_cells + size(), m_cells);
    }

    // 복사 후 교환: 복사가 실패하면 이 객체는 손대지 않은 그대로다.
    Grid& operator=(const Grid& rhs)
    {
        Grid temp{ rhs };   // 1. 사본을 만든다(실패해도 *this는 그대로).
        swap(temp);         // 2. 예외가 없는 교환으로 확정한다.
        return *this;
    }                       // 3. temp가 소멸하며 원래 배열을 지운다.

    void swap(Grid& other) noexcept
    {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_cells, other.m_cells);
    }

    void report(const char* name) const
    {
        std::println("  {}: {}x{}, 배열 {}", name, m_width, m_height,
                     m_cells ? "있음" : "없음(nullptr)");
    }

private:
    std::size_t size() const { return m_width * m_height; }

    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

int main()
{
    Grid big{ 4, 3 };

    Grid a{ 1, 1 };
    g_failNextAllocation = true;
    try {
        a.assignNaive(big);
    } catch (const std::bad_alloc&) {
        std::println("단순한 대입 실패 뒤");
        a.report("a");   // 크기는 4x3인데 배열은 없다: 망가진 상태
    }

    Grid b{ 1, 1 };
    g_failNextAllocation = true;
    try {
        b = big;
    } catch (const std::bad_alloc&) {
        std::println("복사 후 교환 실패 뒤");
        b.report("b");   // 대입 전 그대로
    }
}
