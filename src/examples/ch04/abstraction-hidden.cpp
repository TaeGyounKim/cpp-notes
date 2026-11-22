#include <cstddef>
#include <print>
#include <stdexcept>
#include <vector>

class SeatMap
{
public:
    SeatMap(std::size_t rowCount, std::size_t columnCount)
        : m_rowCount{ rowCount }
        , m_columnCount{ columnCount }
        , m_reserved(rowCount * columnCount, false)
    {
    }

    // 인터페이스: 쓰는 쪽이 아는 것은 이 함수들뿐이다.
    void reserve(std::size_t row, std::size_t column)
    {
        m_reserved[toIndex(row, column)] = true;
    }

    bool isReserved(std::size_t row, std::size_t column) const
    {
        return m_reserved[toIndex(row, column)];
    }

    std::size_t getRowCount() const { return m_rowCount; }
    std::size_t getColumnCount() const { return m_columnCount; }

private:
    // 구현: 2차원 배열이 아니라 한 줄로 편 vector.
    // 바꿔도 쓰는 쪽 코드는 그대로다.
    std::size_t toIndex(std::size_t row, std::size_t column) const
    {
        if (row >= m_rowCount || column >= m_columnCount) {
            throw std::out_of_range{ "no such seat" };
        }
        return row * m_columnCount + column;
    }

    std::size_t m_rowCount;
    std::size_t m_columnCount;
    std::vector<bool> m_reserved;
};

void print(const SeatMap& seats)
{
    for (std::size_t row{ 0 }; row < seats.getRowCount(); ++row) {
        for (std::size_t column{ 0 }; column < seats.getColumnCount();
             ++column) {
            std::print("{}", seats.isReserved(row, column) ? '#' : '.');
        }
        std::println("");
    }
}

int main()
{
    SeatMap seats{ 3, 4 };
    seats.reserve(1, 2);
    seats.reserve(2, 0);
    print(seats);

    try {
        seats.reserve(3, 0);   // 없는 좌석
    } catch (const std::out_of_range& exception) {
        std::println("오류: {}", exception.what());
    }
}
