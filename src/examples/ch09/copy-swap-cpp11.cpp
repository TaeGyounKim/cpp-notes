#include <algorithm>
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
    Grid(const Grid& src) : Grid(src.m_width, src.m_height)   // 위임: C++11
    {
        std::copy(src.m_cells, src.m_cells + m_width * m_height, m_cells);
    }
    ~Grid() { delete[] m_cells; }

    Grid& operator=(const Grid& rhs)
    {
        Grid temp(rhs);
        swap(temp);
        return *this;
    }

    void swap(Grid& other) noexcept   // noexcept: C++11
    {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_cells, other.m_cells);
    }

    std::size_t width() const { return m_width; }

private:
    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

void swap(Grid& first, Grid& second) noexcept { first.swap(second); }

int main()
{
    Grid a(2, 2);
    Grid b(5, 1);
    a = b;
    std::cout << "a의 너비: " << a.width() << '\n';
}
