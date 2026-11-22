#include <cstddef>
#include <print>
#include <vector>

class Grid
{
public:
    class Cell;   // 중첩 클래스: 앞쪽 선언만 하고 아래에서 정의

    // 클래스 안의 열거형
    enum class Unit { Celsius, Fahrenheit };

    Grid(std::size_t width, std::size_t height);
    Cell& at(std::size_t x, std::size_t y);

private:
    std::size_t m_width;
    std::vector<Cell> m_cells;
};

class Grid::Cell   // 바깥에서 정의할 때는 Grid::Cell
{
public:
    Cell() = default;
    void set(double value, Unit unit)   // 바깥 클래스의 Unit을 그냥 씀
    {
        m_celsius = unit == Unit::Celsius ? value : (value - 32.0) * 5.0 / 9.0;
    }
    double celsius() const { return m_celsius; }

private:
    double m_celsius{ 0.0 };
};

Grid::Grid(std::size_t width, std::size_t height)
    : m_width{ width }, m_cells(width * height)
{
}

// 반환 타입에는 Grid::를 붙여야 한다. 매개변수 목록 안에서는 필요 없다.
Grid::Cell& Grid::at(std::size_t x, std::size_t y)
{
    return m_cells[y * m_width + x];
}

int main()
{
    Grid grid{ 2, 2 };
    grid.at(0, 0).set(21.5, Grid::Unit::Celsius);
    grid.at(1, 1).set(212.0, Grid::Unit::Fahrenheit);

    Grid::Cell& cell{ grid.at(1, 1) };   // 밖에서는 Grid::Cell
    std::println("{} {}", grid.at(0, 0).celsius(), cell.celsius());
}
