#include <algorithm>
#include <cstddef>
#include <print>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height },
          m_cells{ new double[width * height]{} }
    {
    }

    // 깊은 복사 생성자: 같은 크기의 배열을 새로 잡고(위임) 값을 복사한다.
    Grid(const Grid& src) : Grid{ src.m_width, src.m_height }
    {
        std::copy(src.m_cells, src.m_cells + size(), m_cells);
    }

    // 깊은 대입 연산자(단순한 버전). 다음 예제에서 문제를 본다.
    Grid& operator=(const Grid& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        delete[] m_cells;                  // 1. 원래 배열을 지운다.
        m_width = rhs.m_width;             // 2. 크기를 바꾼다.
        m_height = rhs.m_height;
        m_cells = new double[size()];      // 3. 새 배열을 잡는다.
        std::copy(rhs.m_cells, rhs.m_cells + size(), m_cells);   // 4. 복사
        return *this;
    }

    ~Grid() { delete[] m_cells; }

    void set(std::size_t i, double value) { m_cells[i] = value; }
    double get(std::size_t i) const { return m_cells[i]; }

private:
    std::size_t size() const { return m_width * m_height; }

    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

int main()
{
    Grid a{ 2, 2 };
    a.set(0, 21.5);

    Grid b{ a };       // 복사: b는 자기 배열을 따로 가진다.
    b.set(0, 99.0);
    std::println("복사 뒤 a: {}, b: {}", a.get(0), b.get(0));

    Grid c{ 3, 1 };
    c = a;             // 대입: c의 원래 배열은 지워지고 새로 잡힌다.
    c.set(0, -5.0);
    std::println("대입 뒤 a: {}, c: {}", a.get(0), c.get(0));
}   // 셋 다 자기 배열을 하나씩 지운다. 이중 해제 없음
