#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T>
class Table
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_cols(cols), m_cells(rows * cols) {}
    T& at(std::size_t row, std::size_t col)
    {
        return m_cells[row * m_cols + col];
    }

private:
    std::size_t m_cols;
    std::vector<T> m_cells;
};

// 전체 특수화와 클래스 템플릿 파생은 C++98부터 있다.
template <>
class Table<const char*>
{
public:
    explicit Table(std::size_t rows = 2, std::size_t cols = 2)
        : m_cols(cols), m_cells(rows * cols) {}
    std::string& at(std::size_t row, std::size_t col)
    {
        return m_cells[row * m_cols + col];
    }

private:
    std::size_t m_cols;
    std::vector<std::string> m_cells;
};

template <typename T>
class MovableTable : public Table<T>
{
public:
    using Table<T>::Table;   // 생성자 상속은 C++11
    void move(std::size_t r1, std::size_t c1, std::size_t r2, std::size_t c2)
    {
        this->at(r2, c2) = this->at(r1, c1);
        this->at(r1, c1) = T();
    }
};

// 별칭 템플릿은 C++11. 그 전에는 구조체 안의 typedef로 흉내 냈다.
template <typename V>
using ByName = std::map<std::string, V>;

int main()
{
    Table<const char*> labels;
    labels.at(0, 0) = "온도";
    MovableTable<int> board(3, 3);
    board.at(0, 0) = 42;
    board.move(0, 0, 2, 2);
    ByName<double> limits;
    limits["습도"] = 60.0;
    std::cout << labels.at(0, 0) << ' ' << board.at(2, 2) << ' '
              << limits["습도"] << '\n';
}
