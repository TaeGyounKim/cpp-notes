#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height);
    ~Grid();
    void set(std::size_t i, double value);
    double get(std::size_t i) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

class Grid::Impl
{
public:
    explicit Impl(std::size_t count) : m_cells(count) {}
    std::vector<double> m_cells;
};

// std::make_unique(C++14) 대신 new를 unique_ptr에 바로 넘긴다.
Grid::Grid(std::size_t width, std::size_t height)
    : m_impl(new Impl(width * height))
{
}
Grid::~Grid() = default;

void Grid::set(std::size_t i, double value) { m_impl->m_cells.at(i) = value; }
double Grid::get(std::size_t i) const { return m_impl->m_cells.at(i); }

int main()
{
    Grid g(3, 2);
    g.set(4, 21.5);
    std::cout << g.get(4) << '\n';
}
