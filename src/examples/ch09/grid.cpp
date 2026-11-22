#include <cstddef>
#include <format>
#include <print>
#include <stdexcept>

// 너비와 높이를 실행 중에 정하는 온도 격자.
// 연습을 위해 맨 포인터로 메모리를 직접 다룬다.
// 실제 코드라면 std::vector<double>을 쓴다.
class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height },
          m_cells{ new double[width * height]{} }   // 모두 0으로
    {
        std::println("  Grid {}x{} 생성", m_width, m_height);
    }

    ~Grid()
    {
        std::println("  Grid {}x{} 소멸: 메모리 반납", m_width, m_height);
        delete[] m_cells;   // 생성자에서 잡은 메모리를 여기서 돌려준다.
        m_cells = nullptr;
    }

    void set(std::size_t x, std::size_t y, double value)
    {
        verifyCoordinate(x, y);
        m_cells[y * m_width + x] = value;
    }

    double get(std::size_t x, std::size_t y) const
    {
        verifyCoordinate(x, y);
        return m_cells[y * m_width + x];
    }

private:
    // set과 get이 같은 검사를 되풀이하지 않도록 한 곳에 모은다.
    void verifyCoordinate(std::size_t x, std::size_t y) const
    {
        if (x >= m_width) {
            throw std::out_of_range{ std::format(
                "x({})는 너비({})보다 작아야 함", x, m_width) };
        }
        if (y >= m_height) {
            throw std::out_of_range{ std::format(
                "y({})는 높이({})보다 작아야 함", y, m_height) };
        }
    }

    std::size_t m_width{ 0 };
    std::size_t m_height{ 0 };
    double* m_cells{ nullptr };   // width * height개의 double
};

int main()
{
    Grid room{ 3, 2 };
    room.set(2, 1, 23.5);
    std::println("(2,1) = {}", room.get(2, 1));

    try {
        room.set(3, 0, 1.0);
    } catch (const std::out_of_range& e) {
        std::println("오류: {}", e.what());
    }
}
