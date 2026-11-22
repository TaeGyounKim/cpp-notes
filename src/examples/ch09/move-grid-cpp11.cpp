#include <cstddef>
#include <iostream>
#include <utility>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width(width), m_height(height),
          m_cells(new double[width * height]())
    {
    }
    ~Grid() { delete[] m_cells; }

    Grid(const Grid&) = delete;              // 이 예에서는 복사를 막음
    Grid& operator=(const Grid&) = delete;

    Grid(Grid&& src) noexcept                // 이동 생성자: C++11
        : m_width(src.m_width), m_height(src.m_height),
          m_cells(src.m_cells)
    {
        // std::exchange(C++14) 대신 원본을 직접 비운다.
        src.m_width = 0;
        src.m_height = 0;
        src.m_cells = nullptr;
    }

    Grid& operator=(Grid&& rhs) noexcept
    {
        if (this != &rhs) {
            delete[] m_cells;
            m_width = rhs.m_width;
            m_height = rhs.m_height;
            m_cells = rhs.m_cells;
            rhs.m_width = 0;
            rhs.m_height = 0;
            rhs.m_cells = nullptr;
        }
        return *this;
    }

    std::size_t width() const { return m_width; }

private:
    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

int main()
{
    Grid a(4, 3);
    Grid b(std::move(a));
    std::cout << "a: " << a.width() << ", b: " << b.width() << '\n';
}
