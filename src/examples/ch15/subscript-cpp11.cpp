#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

// 다차원 첨자(C++23)가 없으므로 operator()로 여러 인수를 받거나,
// 행을 돌려주는 operator[]를 이어 쓴다(b[r][c]).
class Board
{
public:
    Board(std::size_t rows, std::size_t cols)
        : m_cols(cols), m_cells(rows * cols) {}

    int& operator()(std::size_t r, std::size_t c)
    {
        return m_cells[r * m_cols + c];
    }

    int* operator[](std::size_t r) { return &m_cells[r * m_cols]; }

    const int& at(std::size_t r, std::size_t c) const
    {
        if (r * m_cols + c >= m_cells.size()) {
            throw std::out_of_range("범위 밖");
        }
        return m_cells[r * m_cols + c];
    }

private:
    std::size_t m_cols;
    std::vector<int> m_cells;
};

int main()
{
    Board b(2, 3);
    b(1, 2) = 7;
    b[0][1] = 5;
    std::cout << b.at(1, 2) << ' ' << b.at(0, 1) << '\n';
}
