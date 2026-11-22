#include <cstddef>
#include <format>
#include <memory>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = DefaultRows,
                   std::size_t cols = DefaultCols)
        : m_rows{ rows }, m_cols{ cols }
    {
        m_cells.resize(m_rows * m_cols);
    }

    std::optional<T>& at(std::size_t row, std::size_t col);
    const std::optional<T>& at(std::size_t row, std::size_t col) const;

    std::size_t rows() const { return m_rows; }
    std::size_t cols() const { return m_cols; }

    static constexpr std::size_t DefaultRows{ 4 };
    static constexpr std::size_t DefaultCols{ 4 };

private:
    void check(std::size_t row, std::size_t col) const;

    std::vector<std::optional<T>> m_cells;   // 2차원을 1차원으로 펼쳐 저장
    std::size_t m_rows{ 0 };
    std::size_t m_cols{ 0 };
};

// 클래스 밖의 멤버 정의마다 템플릿 머리가 필요하고, 이름은 Table<T>
template <typename T>
void Table<T>::check(std::size_t row, std::size_t col) const
{
    if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range{ std::format(
            "({}, {})는 {}x{} 표 밖", row, col, m_rows, m_cols) };
    }
}

template <typename T>
const std::optional<T>& Table<T>::at(std::size_t row, std::size_t col) const
{
    check(row, col);
    return m_cells[row * m_cols + col];
}

template <typename T>
std::optional<T>& Table<T>::at(std::size_t row, std::size_t col)
{
    // const 판을 불러 중복을 피한다(9장).
    return const_cast<std::optional<T>&>(std::as_const(*this).at(row, col));
}

int main()
{
    Table<int> scores;                 // 기본 4x4
    scores.at(0, 1) = 87;
    std::println("{} {}", scores.at(0, 1).value_or(-1),
                 scores.at(2, 2).value_or(-1));    // 빈 칸은 -1

    Table<std::string> names{ 2, 3 };
    names.at(1, 2) = "센서-7";
    Table<std::string> copy{ names };  // 복사 생성자는 컴파일러가 만든다.
    std::println("{} ({}x{})", copy.at(1, 2).value(), copy.rows(), copy.cols());

    Table<std::vector<int>> series{ 1, 1 };
    series.at(0, 0) = std::vector{ 3, 1, 4 };
    std::println("길이 {}", series.at(0, 0)->size());

    auto onHeap{ std::make_unique<Table<double>>(2, 2) };
    onHeap->at(1, 1) = 0.5;
    std::println("{}", onHeap->at(1, 1).value_or(0.0));

    try {
        scores.at(4, 0) = 1;
    } catch (const std::out_of_range& e) {
        std::println("오류: {}", e.what());
    }
}
