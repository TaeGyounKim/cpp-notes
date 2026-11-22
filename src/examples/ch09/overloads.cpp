#include <charconv>
#include <cstddef>
#include <print>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height }, m_cells(width * height)
    {
    }

    // 이름이 같고 매개변수 타입이 다른 오버로드
    void set(std::size_t x, std::size_t y, double value)
    {
        at(x, y) = value;
    }
    void set(std::size_t x, std::size_t y, std::string_view text)
    {
        double value{ 0.0 };
        std::from_chars(text.data(), text.data() + text.size(), value);
        at(x, y) = value;
    }
    // 정수로 부르는 것은 막는다.
    void set(std::size_t x, std::size_t y, int value) = delete;

    // const에 따른 오버로드
    const double& at(std::size_t x, std::size_t y) const
    {
        std::println("    (const판 at)");
        verifyCoordinate(x, y);
        return m_cells[y * m_width + x];
    }
    double& at(std::size_t x, std::size_t y)
    {
        std::println("    (비const판 at -> const판에 맡김)");
        // const판에 맡기고, 돌려받은 const 참조에서 const를 벗긴다.
        return const_cast<double&>(std::as_const(*this).at(x, y));
    }

private:
    void verifyCoordinate(std::size_t x, std::size_t y) const
    {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range{ "좌표가 범위 밖" };
        }
    }

    std::size_t m_width;
    std::size_t m_height;
    std::vector<double> m_cells;
};

int main()
{
    Grid grid{ 3, 2 };
    std::println("set(double)");
    grid.set(0, 0, 21.5);
    std::println("set(string_view)");
    grid.set(1, 0, "18.25");
    // grid.set(2, 0, 30);   // 컴파일 오류: 지워진 오버로드

    std::println("비const 객체로 at");
    grid.at(2, 1) = -4.0;     // double&를 돌려받아 값을 바꾼다.

    const Grid& view{ grid };
    std::println("const 참조로 at");
    std::println("  {} {} {}", view.at(0, 0), view.at(1, 0), view.at(2, 1));
}
