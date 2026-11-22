// 실제로는 세 부분이 서로 다른 파일에 있다.
// (1) 인터페이스 클래스 정의: 헤더나 모듈 인터페이스 파일. 사용자가 보는 곳
// (2) 구현 클래스 정의, (3) 멤버 함수 정의: 구현 파일. 사용자는 보지 않는다.
#include <cstddef>
#include <memory>
#include <print>
#include <utility>
#include <vector>

// ---- (1) 인터페이스 클래스: 데이터 멤버는 포인터 하나뿐 ----
class Grid
{
public:
    Grid(std::size_t width, std::size_t height);
    Grid(const Grid& src);
    Grid(Grid&&) noexcept;
    ~Grid();
    Grid& operator=(const Grid& rhs);
    Grid& operator=(Grid&&) noexcept;

    void set(std::size_t x, std::size_t y, double value);
    double get(std::size_t x, std::size_t y) const;
    void swap(Grid& other) noexcept;

private:
    class Impl;                     // 앞쪽 선언만. 내용은 숨김
    std::unique_ptr<Impl> m_impl;   // 구현 객체를 가리키는 포인터
};

// ---- (2) 구현 클래스: 바뀌어도 (1)을 쓰는 코드는 다시 컴파일할 필요 없음 ----
class Grid::Impl
{
public:
    Impl(std::size_t width, std::size_t height)
        : m_width{ width }, m_cells(width * height)
    {
    }
    void set(std::size_t x, std::size_t y, double v) { at(x, y) = v; }
    double get(std::size_t x, std::size_t y) const
    {
        return m_cells.at(y * m_width + x);
    }

private:
    double& at(std::size_t x, std::size_t y)
    {
        return m_cells.at(y * m_width + x);
    }
    std::size_t m_width;
    std::vector<double> m_cells;
};

// ---- (3) 인터페이스 클래스의 멤버 함수: 구현 객체에 일을 넘긴다 ----
Grid::Grid(std::size_t width, std::size_t height)
    : m_impl{ std::make_unique<Impl>(width, height) }
{
}
Grid::Grid(const Grid& src) : m_impl{ std::make_unique<Impl>(*src.m_impl) }
{
}
Grid::Grid(Grid&&) noexcept = default;   // Impl이 완전한 타입인 여기서
Grid::~Grid() = default;                 // 기본 정의한다.
Grid& Grid::operator=(Grid&&) noexcept = default;

Grid& Grid::operator=(const Grid& rhs)
{
    *m_impl = *rhs.m_impl;   // 포인터가 아니라 Impl 객체끼리 대입
    return *this;
}

void Grid::set(std::size_t x, std::size_t y, double value)
{
    m_impl->set(x, y, value);
}
double Grid::get(std::size_t x, std::size_t y) const
{
    return m_impl->get(x, y);
}
void Grid::swap(Grid& other) noexcept { std::swap(m_impl, other.m_impl); }

// ---- 사용하는 쪽: (1)만 안다 ----
int main()
{
    Grid a{ 3, 2 };
    a.set(1, 1, 21.5);
    Grid b{ a };       // 복사: Impl까지 복사됨
    b.set(1, 1, 99.0);
    std::println("a: {}, b: {}", a.get(1, 1), b.get(1, 1));
    a.swap(b);         // 포인터만 맞바꿈
    std::println("swap 뒤 a: {}, b: {}", a.get(1, 1), b.get(1, 1));
}
