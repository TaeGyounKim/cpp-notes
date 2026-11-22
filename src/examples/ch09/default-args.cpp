#include <cstddef>
#include <print>
#include <vector>

class Grid
{
public:
    // 기본 인수: 선언에만 적는다. 오른쪽부터 연속해서.
    explicit Grid(std::size_t width = 10, std::size_t height = 10)
        : m_width{ width }, m_height{ height }, m_cells(width * height)
    {
    }
    // Grid() = default;   // 함께 두면 Grid g;가 모호해진다.

    void print() const { std::println("{}x{}", m_width, m_height); }

private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<double> m_cells;
};

int main()
{
    Grid a;          // 10x10: 모든 매개변수에 기본값이 있으니 기본 생성자 역할
    Grid b{ 5 };     // 5x10
    Grid c{ 5, 6 };  // 5x6
    a.print();
    b.print();
    c.print();
}
