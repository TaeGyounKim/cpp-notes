#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Grid
{
public:
    Grid(std::string name, std::size_t width, std::size_t height)
        : m_name(std::move(name)), m_width(width), m_height(height),
          m_cells(width * height)
    {
    }

    void set(std::size_t x, std::size_t y, double value)
    {
        m_cells.at(y * m_width + x) = value;
    }
    double get(std::size_t x, std::size_t y) const
    {
        return m_cells.at(y * m_width + x);
    }

private:
    std::string m_name;
    std::size_t m_width;
    std::size_t m_height;
    std::vector<double> m_cells;   // 특별 멤버 함수가 필요 없다.
};

int main()
{
    Grid a("a", 3, 2);
    a.set(1, 1, 21.5);
    Grid b(a);
    b.set(1, 1, 99.0);
    std::cout << a.get(1, 1) << ' ' << b.get(1, 1) << '\n';
}
