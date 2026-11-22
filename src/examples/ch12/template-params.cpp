#include <cstddef>
#include <optional>
#include <print>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// 타입이 아닌 템플릿 매개변수 ROWS, COLS와 기본값
template <typename T = int, std::size_t ROWS = 3, std::size_t COLS = 3>
class FixedTable
{
public:
    std::optional<T>& at(std::size_t row, std::size_t col)
    {
        return m_cells[row][col];
    }
    std::size_t rows() const { return ROWS; }
    std::size_t cols() const { return COLS; }

private:
    std::optional<T> m_cells[ROWS][COLS];   // 크기를 컴파일할 때 안다.
};

constexpr std::size_t pickCols() { return 5; }

// 생성자 인수에서 T를 추론하는 클래스 템플릿
template <typename T>
class Label
{
public:
    explicit Label(T text) : m_text{ std::move(text) } {}
    const T& text() const { return m_text; }

private:
    T m_text;
};

// 사용자 정의 추론 가이드: const char*를 받으면 Label<std::string>
Label(const char*) -> Label<std::string>;

int main()
{
    FixedTable<double, 2, pickCols()> a;   // constexpr 함수의 결과도 된다.
    a.at(1, 4) = 0.5;
    std::println("{}x{}, {}", a.rows(), a.cols(), a.at(1, 4).value_or(0));

    FixedTable<> b;                         // int, 3, 3
    FixedTable<std::string, 2> c;           // std::string, 2, 3
    std::println("{}x{} / {}x{}", b.rows(), b.cols(), c.rows(), c.cols());

    // 크기가 타입의 일부다.
    std::println("같은 타입? {}",
        std::is_same_v<FixedTable<int, 2, 2>, FixedTable<int, 2, 3>>);

    // 클래스 템플릿 인수 추론(CTAD)
    std::pair p{ 1, 2.5 };                  // std::pair<int, double>
    std::vector v{ 3, 1, 4 };               // std::vector<int>
    std::println("{} {}", std::is_same_v<decltype(p), std::pair<int, double>>,
                 std::is_same_v<decltype(v), std::vector<int>>);

    Label name{ "센서-7" };                 // 가이드 덕분에 Label<std::string>
    std::println("{} {}", name.text().size(),
                 std::is_same_v<decltype(name), Label<std::string>>);
}
