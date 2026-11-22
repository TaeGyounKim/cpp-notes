#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

// 타입이 아닌 매개변수와 기본값은 C++11에서도 그대로 쓴다.
template <typename T = int, std::size_t ROWS = 3, std::size_t COLS = 3>
class FixedTable
{
public:
    T& at(std::size_t row, std::size_t col) { return m_cells[row][col]; }
    std::size_t rows() const { return ROWS; }
    std::size_t cols() const { return COLS; }

private:
    T m_cells[ROWS][COLS] = {};
};

template <typename T>
class Label
{
public:
    explicit Label(T text) : m_text(std::move(text)) {}
    const T& text() const { return m_text; }

private:
    T m_text;
};

// CTAD(C++17)가 없으므로 make_ 도우미 함수를 둔다.
inline Label<std::string> makeLabel(const char* text)
{
    return Label<std::string>(text);
}

int main()
{
    FixedTable<> b;                       // C++11에서는 <>가 필요하다.
    b.at(0, 0) = 7;
    std::cout << b.rows() << 'x' << b.cols() << ' ' << b.at(0, 0) << '\n';

    auto p = std::make_pair(1, 2.5);      // std::pair<int, double>
    auto name = makeLabel("센서-7");
    std::cout << p.second << ' ' << name.text() << '\n';
}
