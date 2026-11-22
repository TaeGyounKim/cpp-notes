#include <cstddef>
#include <deque>
#include <iostream>
#include <memory>
#include <vector>

// 콘셉트(C++20)와 optional(C++17)이 없고, 실수·클래스 타입의
// 타입이 아닌 매개변수(C++20)도 없다. 나머지는 C++11에서 된다.
template <typename T,
          template <typename E, typename A = std::allocator<E> > class Storage
              = std::vector>
class Table2 {
public:
    explicit Table2(std::size_t rows = 3, std::size_t cols = 3)
        : m_cells(rows * cols), m_cols(cols) {}
    T& at(std::size_t r, std::size_t c) { return m_cells[r * m_cols + c]; }
private:
    Storage<T> m_cells;
    std::size_t m_cols;
};

template <typename T, T Fill = T()>
class FilledTable {
public:
    explicit FilledTable(std::size_t n = 4) : m_cells(n, Fill) {}
    const T& at(std::size_t i) const { return m_cells[i]; }
private:
    std::vector<T> m_cells;
};

int main()
{
    Table2<int> c;
    Table2<int, std::deque> d;
    c.at(2, 2) = 9;
    d.at(1, 1) = 4;
    FilledTable<int, -1> minus;
    std::cout << c.at(2, 2) << ' ' << d.at(1, 1) << ' ' << minus.at(0)
              << '\n';
}
