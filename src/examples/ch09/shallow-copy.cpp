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

    void set(std::size_t i, double value) { m_cells[i] = value; }
    double get(std::size_t i) const { return m_cells[i]; }

    // 복사 생성자와 대입 연산자를 쓰지 않았다.
    // 컴파일러가 만든 것은 포인터 m_cells의 "값(주소)"만 복사한다.

private:
    std::size_t m_width;
    std::size_t m_height;
    double* m_cells;
};

void show(Grid g)   // 값으로 받는다: 얕은 복사가 일어난다.
{
    std::println(stderr, "show 안: {}", g.get(0));
}   // g가 소멸하며 m_cells가 가리키는 메모리를 지운다.

int main()
{
    Grid room{ 2, 2 };
    room.set(0, 21.5);
    show(room);
    // room.m_cells는 이미 지워진 메모리를 가리킨다(댕글링 포인터).
    std::println(stderr, "show 뒤: {}", room.get(0));
}
