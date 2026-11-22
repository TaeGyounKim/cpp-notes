#include <concepts>
#include <cstddef>
#include <deque>
#include <memory>
#include <optional>
#include <print>
#include <ranges>
#include <vector>

// 1) 타입 매개변수로 저장 컨테이너를 받는다(기본값 vector).
template <typename C>
concept TableStorage = std::ranges::random_access_range<C> && requires(C c) {
    typename C::value_type;
    c.resize(1);
};

template <typename T, TableStorage Storage = std::vector<std::optional<T>>>
class Table {
public:
    explicit Table(std::size_t rows = 3, std::size_t cols = 3)
        : m_cols{ cols } { m_cells.resize(rows * cols); }
    // Storage::value_type은 의존 이름이므로 typename이 필요하다.
    typename Storage::value_type& at(std::size_t r, std::size_t c)
    {
        return m_cells[r * m_cols + c];
    }
private:
    Storage m_cells;
    std::size_t m_cols;
};

// 2) 템플릿 템플릿 매개변수: 컨테이너 "템플릿"을 받아 원소 타입은 직접 채운다.
template <typename T,
          template <typename E, typename A = std::allocator<E>> class Storage
              = std::vector>
class Table2 {
public:
    explicit Table2(std::size_t rows = 3, std::size_t cols = 3)
        : m_cols{ cols } { m_cells.resize(rows * cols); }
    std::optional<T>& at(std::size_t r, std::size_t c)
    {
        return m_cells[r * m_cols + c];
    }
private:
    Storage<std::optional<T>> m_cells;   // 여기서 원소 타입을 정한다.
    std::size_t m_cols;
};

// 3) 타입이 아닌 매개변수의 타입으로 앞의 타입 매개변수를 쓴다.
template <typename T, T Fill = T{}>
class FilledTable {
public:
    explicit FilledTable(std::size_t n = 4) : m_cells(n, Fill) {}
    const T& at(std::size_t i) const { return m_cells[i]; }
private:
    std::vector<T> m_cells;
};

// C++20: 실수와 "구조적" 클래스 타입도 타입이 아닌 매개변수가 될 수 있다.
struct Range {
    int lo;
    int hi;   // public 멤버만, 상수 표현식으로 만들 수 있는 리터럴 타입
};
template <double Scale, Range R>
int scaled(int v)
{
    int x{ static_cast<int>(v * Scale) };
    return x < R.lo ? R.lo : (x > R.hi ? R.hi : x);
}

int main()
{
    Table<int> a;                                     // 기본: vector
    Table<int, std::deque<std::optional<int>>> b;     // deque로
    a.at(1, 2) = 5;
    b.at(0, 0) = 7;
    std::println("{} {}", a.at(1, 2).value_or(0), b.at(0, 0).value_or(0));
    // Table<int, double> bad;   // 오류: double은 TableStorage가 아님

    Table2<int> c;                                    // vector<optional<int>>
    Table2<int, std::deque> d;                        // deque<optional<int>>
    c.at(2, 2) = 9;
    d.at(1, 1) = 4;
    std::println("{} {}", c.at(2, 2).value_or(0), d.at(1, 1).value_or(0));

    FilledTable<int> zeros;
    FilledTable<int, -1> minus;
    FilledTable<char, '#'> hashes;
    std::println("{} {} {}", zeros.at(0), minus.at(3), hashes.at(2));

    std::println("{} {}", scaled<1.5, Range{ 0, 100 }>(50),
                 scaled<1.5, Range{ 0, 100 }>(90));
}
