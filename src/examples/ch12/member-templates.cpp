#include <cstddef>
#include <optional>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_rows{ rows }, m_cols{ cols }
    {
        m_cells.resize(rows * cols);
    }

    // 다른 원소 타입 E의 표에서 변환하는 생성자와 대입 연산자
    template <typename E>
    Table(const Table<E>& src);
    template <typename E>
    Table& operator=(const Table<E>& rhs);

    void swap(Table& other) noexcept
    {
        std::swap(m_rows, other.m_rows);
        std::swap(m_cols, other.m_cols);
        std::swap(m_cells, other.m_cells);
    }

    // C++23: this 추론. const 판과 비 const 판을 함수 하나로
    template <typename Self>
    auto&& at(this Self&& self, std::size_t row, std::size_t col)
    {
        if (row >= self.m_rows || col >= self.m_cols) {
            throw std::out_of_range{ "표 밖" };
        }
        return std::forward_like<Self>(self.m_cells[row * self.m_cols + col]);
    }

    std::size_t rows() const { return m_rows; }
    std::size_t cols() const { return m_cols; }

private:
    std::vector<std::optional<T>> m_cells;
    std::size_t m_rows{ 0 };
    std::size_t m_cols{ 0 };
};

// 클래스 템플릿 머리 뒤에 멤버 템플릿 머리가 따로 온다.
template <typename T>
template <typename E>
Table<T>::Table(const Table<E>& src)
    : Table{ src.rows(), src.cols() }
{
    // src는 다른 타입이라 private 멤버에 접근할 수 없다. public 멤버로
    for (std::size_t r{ 0 }; r < m_rows; ++r) {
        for (std::size_t c{ 0 }; c < m_cols; ++c) {
            if (src.at(r, c)) { at(r, c) = static_cast<T>(*src.at(r, c)); }
        }
    }
}

template <typename T>
template <typename E>
Table<T>& Table<T>::operator=(const Table<E>& rhs)
{
    Table<T> temp{ rhs };   // 복사 후 맞바꾸기(9장)
    swap(temp);
    return *this;
}

int main()
{
    Table<int> counts;
    counts.at(0, 0) = 3;
    counts.at(1, 1) = 4;

    Table<double> ratios{ counts };      // Table<int> -> Table<double>
    ratios.at(1, 1) = *ratios.at(1, 1) / 8;
    std::println("{} {}", ratios.at(0, 0).value_or(-1),
                 ratios.at(1, 1).value_or(-1));

    Table<double> other{ 3, 3 };
    other = counts;                      // 변환 대입
    std::println("{}x{}, 빈 칸 {}", other.rows(), other.cols(),
                 other.at(0, 1).has_value());

    const Table<int>& view{ counts };
    // view.at(0, 0) = 9;                // const 객체라 const optional&
    std::println("{}", view.at(0, 0).value());
}
