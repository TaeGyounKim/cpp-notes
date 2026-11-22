#include <cstddef>
#include <memory>
#include <print>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

// 필요한 만큼 자라는 배열
template <typename T>
class GrowArray
{
public:
    // 쓰기용: 범위 밖이면 늘린다. 참조를 돌려주므로 대입의 왼쪽에 쓸 수 있다.
    T& operator[](std::size_t i)
    {
        if (i >= m_size) { resize(i + Extra); }
        return m_data[i];
    }
    // 읽기용(const 객체): 늘리지 않고 예외를 던진다.
    const T& operator[](std::size_t i) const
    {
        if (i >= m_size) { throw std::out_of_range{ "범위 밖" }; }
        return m_data[i];
    }
    std::size_t size() const noexcept { return m_size; }

private:
    static constexpr std::size_t Extra{ 4 };
    void resize(std::size_t newSize)
    {
        auto bigger{ std::make_unique<T[]>(newSize) };   // 영 초기화
        for (std::size_t i{ 0 }; i < m_size; ++i) { bigger[i] = m_data[i]; }
        m_data = std::move(bigger);   // 복사가 끝난 뒤에야 바꾼다(강한 보장).
        m_size = newSize;
    }
    std::unique_ptr<T[]> m_data;
    std::size_t m_size{ 0 };
};

void show(const GrowArray<int>& a)   // const 참조: const operator[]가 불린다.
{
    for (std::size_t i{ 0 }; i < a.size(); ++i) { std::print("{} ", a[i]); }
    std::println("");
}

// C++23: 인수가 여럿인 첨자 연산자
class Board
{
public:
    Board(std::size_t rows, std::size_t cols)
        : m_cols{ cols }, m_cells(rows * cols) {}
    int& operator[](std::size_t r, std::size_t c)
    {
        return m_cells[r * m_cols + c];
    }

private:
    std::size_t m_cols;
    std::vector<int> m_cells;
};

// C++23: this가 필요 없는 static 첨자 연산자. 정수가 아닌 첨자도 된다.
enum class Level { Low, Mid, High };
struct LevelName
{
    static constexpr std::string_view operator[](Level level) noexcept
    {
        switch (level) {
        case Level::Low: return "낮음";
        case Level::Mid: return "보통";
        case Level::High: return "높음";
        }
        return "?";
    }
};

int main()
{
    GrowArray<int> a;
    for (std::size_t i{ 0 }; i < 10; i += 3) { a[i] = 100 + i; }
    show(a);

    try {
        const GrowArray<int>& view{ a };
        std::println("{}", view[50]);
    } catch (const std::out_of_range& e) {
        std::println("const 판: {}", e.what());
    }

    Board b{ 2, 3 };
    b[1, 2] = 7;
    std::println("b[1, 2] = {}", b[1, 2]);

    std::println("{} {}", LevelName{}[Level::High],
                 LevelName::operator[](Level::Low));
}
