#include <cstddef>
#include <print>
#include <string>
#include <vector>

// 칸에 무엇을 담을지를 정하지 않은 격자.
// CellType 자리에 타입을 넣어 쓴다.
template <typename CellType>
class Grid
{
public:
    Grid(std::size_t rowCount, std::size_t columnCount)
        : m_columnCount{ columnCount }
        , m_cells(rowCount * columnCount)
    {
    }

    void set(std::size_t row, std::size_t column, const CellType& value)
    {
        m_cells[row * m_columnCount + column] = value;
    }

    const CellType& get(std::size_t row, std::size_t column) const
    {
        return m_cells[row * m_columnCount + column];
    }

private:
    std::size_t m_columnCount;
    std::vector<CellType> m_cells;
};

int main()
{
    // 같은 Grid를 서로 다른 프로그램에 쓴다.

    // 오목판: 칸마다 돌 하나(문자)
    Grid<char> board{ 15, 15 };
    board.set(7, 7, 'B');
    std::println("가운데 돌: {}", board.get(7, 7));

    // 시간표: 칸마다 과목 이름(문자열)
    Grid<std::string> timetable{ 5, 6 };
    timetable.set(0, 2, "C++");
    std::println("월요일 3교시: {}", timetable.get(0, 2));

    // 온도 지도: 칸마다 실수
    Grid<double> heatmap{ 2, 2 };
    heatmap.set(1, 1, 36.5);
    std::println("온도: {}", heatmap.get(1, 1));
}
