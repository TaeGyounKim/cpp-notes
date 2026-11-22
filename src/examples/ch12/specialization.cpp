#include <cstddef>
#include <map>
#include <optional>
#include <print>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_cols{ cols }, m_cells(rows * cols) {}
    std::optional<T>& at(std::size_t row, std::size_t col)
    {
        return m_cells[row * m_cols + col];
    }

private:
    std::size_t m_cols{ 0 };
    std::vector<std::optional<T>> m_cells;
};

// 전체 특수화: const char*는 포인터 대신 std::string으로 깊게 복사해 둔다.
template <>
class Table<const char*>
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_cols{ cols }, m_cells(rows * cols) {}
    std::optional<std::string>& at(std::size_t row, std::size_t col);

private:
    std::size_t m_cols{ 0 };
    std::vector<std::optional<std::string>> m_cells;
};

// 특수화의 멤버 정의 앞에는 template<>를 다시 쓰지 않는다.
std::optional<std::string>& Table<const char*>::at(std::size_t row,
                                                   std::size_t col)
{
    return m_cells[row * m_cols + col];
}

// 클래스 템플릿에서 파생한 클래스 템플릿
template <typename T>
class MovableTable : public Table<T>
{
public:
    using Table<T>::Table;     // 생성자 상속(10장)

    void move(std::size_t r1, std::size_t c1, std::size_t r2, std::size_t c2)
    {
        // 기반 클래스 템플릿의 멤버는 this-> 또는 Table<T>::로 부른다.
        this->at(r2, c2) = std::move(this->at(r1, c1));
        this->at(r1, c1).reset();
    }
};

// 별칭 템플릿: 일부 템플릿 인수만 고정한다.
template <typename V>
using ByName = std::map<std::string, V>;

int main()
{
    char buffer[]{ "온도" };
    Table<const char*> labels;
    labels.at(0, 0) = buffer;              // std::string으로 복사된다.
    buffer[0] = '?';                       // 원본을 바꿔도
    std::println("{}", *labels.at(0, 0));  // 표의 값은 그대로

    MovableTable<int> board{ 3, 3 };
    board.at(0, 0) = 42;
    board.move(0, 0, 2, 2);
    std::println("{} {}", board.at(0, 0).has_value(), *board.at(2, 2));

    ByName<double> limits{ { "온도", 30.5 }, { "습도", 60.0 } };
    std::println("{}", limits["온도"]);
}
