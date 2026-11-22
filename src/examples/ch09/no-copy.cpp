#include <cstddef>
#include <print>

class Grid
{
public:
    Grid(std::size_t width, std::size_t height)
        : m_width{ width }, m_height{ height },
          m_cells{ new double[width * height]{} }
    {
    }
    ~Grid() { delete[] m_cells; }

    // 복사와 대입을 아예 막는다. 정의는 쓰지 않는다.
    Grid(const Grid& src) = delete;
    Grid& operator=(const Grid& rhs) = delete;

    std::size_t width() const { return m_width; }

private:
    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

void show(const Grid& g)   // const 참조로는 넘길 수 있다.
{
    std::println("너비 {}", g.width());
}

int main()
{
    Grid a{ 3, 2 };
    show(a);
    // Grid b{ a };   // 컴파일 오류: 복사 생성자가 지워짐
    // a = a;         // 컴파일 오류: 대입 연산자가 지워짐
}
