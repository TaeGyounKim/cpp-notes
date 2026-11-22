#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class Grid
{
public:
    explicit Grid(std::size_t width = 3, std::size_t height = 2)
        : m_width(width), m_height(height), m_cells(width * height)
    {
    }

    void set(std::size_t x, std::size_t y, double value) { at(x, y) = value; }
    void set(std::size_t x, std::size_t y, int value) = delete;   // C++11

    const double& at(std::size_t x, std::size_t y) const
    {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range("좌표가 범위 밖");
        }
        return m_cells[y * m_width + x];
    }
    double& at(std::size_t x, std::size_t y)
    {
        // std::as_const(C++17) 대신 static_cast로 const 참조를 만든다.
        return const_cast<double&>(
            static_cast<const Grid&>(*this).at(x, y));
    }

    // 참조 한정(C++11): 좌측값에만 대입
    Grid& operator=(const Grid& rhs) & = default;

private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<double> m_cells;
};

int main()
{
    Grid grid;
    grid.set(0, 0, 21.5);
    grid.at(1, 1) = -4.0;
    const Grid& view = grid;
    std::cout << view.at(0, 0) << ' ' << view.at(1, 1) << '\n';
}
