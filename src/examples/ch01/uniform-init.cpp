#include <print>
#include <vector>

struct CircleStruct
{
    int x;
    int y;
    double radius;
};

class CircleClass
{
public:
    CircleClass(int x, int y, double radius)
        : m_x{ x }, m_y{ y }, m_radius{ radius }
    {
    }

    double getRadius() { return m_radius; }

private:
    int m_x;
    int m_y;
    double m_radius;
};

int main()
{
    // 구조체도 클래스도 같은 모양으로 초기화한다.
    CircleStruct circle1{ 10, 10, 2.5 };
    CircleClass circle2{ 10, 10, 2.5 };   // 생성자가 호출된다.
    std::println("{} {}", circle1.radius, circle2.getRadius());

    // 기본 타입: 네 줄 모두 3으로 초기화된다.
    int a = 3;
    int b(3);
    int c = { 3 };
    int d{ 3 };
    std::println("{} {} {} {}", a, b, c, d);

    // 빈 중괄호: 0으로 초기화. 구조체는 모든 필드가 0
    int e{};
    CircleStruct empty{};
    std::println("{} {} {} {}", e, empty.x, empty.y, empty.radius);

    // 컨테이너
    std::vector<int> numbers{ 1, 2, 3 };
    std::println("{}", numbers);
}
