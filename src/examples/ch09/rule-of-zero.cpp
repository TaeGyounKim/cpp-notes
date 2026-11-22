#include <cstddef>
#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 영의 규칙: 자원 관리는 vector와 string에 맡긴다.
// 소멸자, 복사·이동 생성자, 복사·이동 대입을 하나도 쓰지 않는다.
class Grid
{
public:
    Grid(std::string name, std::size_t width, std::size_t height)
        : m_name{ std::move(name) }, m_width{ width }, m_height{ height },
          m_cells(width * height)   // ()로 크기 지정. 0으로 채워진다.
    {
    }

    void set(std::size_t x, std::size_t y, double value)
    {
        m_cells.at(y * m_width + x) = value;   // at(): 범위 밖이면 예외
    }
    double get(std::size_t x, std::size_t y) const
    {
        return m_cells.at(y * m_width + x);
    }
    std::size_t width() const { return m_width; }

private:
    std::string m_name;
    std::size_t m_width;
    std::size_t m_height;
    std::vector<double> m_cells;   // 메모리를 알아서 관리한다.
};

int main()
{
    Grid a{ "a", 3, 2 };
    a.set(1, 1, 21.5);

    Grid b{ a };               // 깊은 복사: vector가 알아서
    b.set(1, 1, 99.0);
    std::println("a: {}, b: {}", a.get(1, 1), b.get(1, 1));

    Grid c{ std::move(a) };    // 이동: 이것도 알아서
    std::println("c: {}, 옮겨진 a의 너비: {}", c.get(1, 1), a.width());

    try {
        c.set(3, 0, 1.0);
    } catch (const std::out_of_range&) {
        std::println("범위 밖 좌표");
    }
}
