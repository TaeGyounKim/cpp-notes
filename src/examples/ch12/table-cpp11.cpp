#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// C++11: std::optional(C++17)이 없으므로 값과 "채워짐" 표시를 따로 둔다.
template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = 4, std::size_t cols = 4)
        : m_rows(rows), m_cols(cols),
          m_cells(rows * cols), m_filled(rows * cols, false) {}

    void set(std::size_t row, std::size_t col, const T& value)
    {
        check(row, col);
        m_cells[row * m_cols + col] = value;
        m_filled[row * m_cols + col] = true;
    }

    // 빈 칸이면 fallback을 돌려준다(value_or 대신).
    T get(std::size_t row, std::size_t col, const T& fallback) const
    {
        check(row, col);
        std::size_t i = row * m_cols + col;
        return m_filled[i] ? m_cells[i] : fallback;
    }

private:
    void check(std::size_t row, std::size_t col) const
    {
        if (row >= m_rows || col >= m_cols) {
            throw std::out_of_range("표 밖의 좌표");
        }
    }

    std::size_t m_rows;
    std::size_t m_cols;
    std::vector<T> m_cells;
    std::vector<bool> m_filled;
};

int main()
{
    Table<int> scores;
    scores.set(0, 1, 87);
    std::cout << scores.get(0, 1, -1) << ' ' << scores.get(2, 2, -1) << '\n';

    Table<std::string> names(2, 3);
    names.set(1, 2, "센서-7");
    std::cout << names.get(1, 2, "(빈 칸)") << '\n';
}
