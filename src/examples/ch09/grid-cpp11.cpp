#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width(width), m_height(height),
          m_cells(new double[width * height]())   // ()로 0 초기화
    {
    }
    ~Grid() { delete[] m_cells; }

    void set(std::size_t x, std::size_t y, double value)
    {
        verifyCoordinate(x, y);
        m_cells[y * m_width + x] = value;
    }

private:
    void verifyCoordinate(std::size_t x, std::size_t y) const
    {
        if (x >= m_width) {   // std::format(C++20) 대신 문자열 이어 붙이기
            throw std::out_of_range("x(" + std::to_string(x)
                                    + ")는 너비보다 작아야 함");
        }
        if (y >= m_height) {
            throw std::out_of_range("y(" + std::to_string(y)
                                    + ")는 높이보다 작아야 함");
        }
    }

    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

int main()
{
    Grid room(3, 2);
    try {
        room.set(3, 0, 1.0);
    } catch (const std::out_of_range& e) {
        std::cout << "오류: " << e.what() << '\n';
    }
}
