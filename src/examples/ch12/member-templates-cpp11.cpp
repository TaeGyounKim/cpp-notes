#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// 멤버 함수 템플릿은 C++98부터 있다. this 추론(C++23)은 없으므로
// const 판과 비 const 판 at()을 따로 쓴다.
template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_rows(rows), m_cols(cols), m_cells(rows * cols) {}

    template <typename E>
    Table(const Table<E>& src) : Table(src.rows(), src.cols())
    {
        for (std::size_t r = 0; r < m_rows; ++r) {
            for (std::size_t c = 0; c < m_cols; ++c) {
                at(r, c) = static_cast<T>(src.at(r, c));
            }
        }
    }

    T& at(std::size_t row, std::size_t col)
    {
        return m_cells[row * m_cols + col];
    }
    const T& at(std::size_t row, std::size_t col) const
    {
        return m_cells[row * m_cols + col];
    }
    std::size_t rows() const { return m_rows; }
    std::size_t cols() const { return m_cols; }

private:
    std::size_t m_rows;
    std::size_t m_cols;
    std::vector<T> m_cells;
};

int main()
{
    Table<int> counts;
    counts.at(1, 1) = 4;
    Table<double> ratios(counts);
    ratios.at(1, 1) /= 8;
    std::cout << ratios.at(1, 1) << '\n';
}
