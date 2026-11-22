#include <print>
#include <string>

// 설계 없이 "쉬운 것부터" 만든 결과.
// 원을 먼저 만들고, 그다음 사각형을 만들었다.

class Circle
{
public:
    Circle(int x, int y, std::string color, int radius)
        : m_x{ x }, m_y{ y }, m_color{ color }, m_radius{ radius }
    {
    }

    void move(int dx, int dy)
    {
        m_x += dx;
        m_y += dy;
    }

    void draw() const
    {
        std::println("원 ({}, {}) {} 반지름 {}", m_x, m_y, m_color, m_radius);
    }

private:
    int m_x;
    int m_y;
    std::string m_color;
    int m_radius;
};

class Rectangle
{
public:
    Rectangle(int x, int y, std::string color, int width, int height)
        : m_x{ x }, m_y{ y }, m_color{ color }
        , m_width{ width }, m_height{ height }
    {
    }

    // Circle의 move와 글자 하나 다르지 않다.
    void move(int dx, int dy)
    {
        m_x += dx;
        m_y += dy;
    }

    void draw() const
    {
        std::println("사각형 ({}, {}) {} {}x{}", m_x, m_y, m_color, m_width,
                     m_height);
    }

private:
    int m_x;
    int m_y;
    std::string m_color;
    int m_width;
    int m_height;
};

int main()
{
    Circle circle{ 10, 10, "red", 5 };
    Rectangle rectangle{ 0, 0, "blue", 4, 3 };

    circle.move(5, 0);
    rectangle.move(1, 1);

    circle.draw();
    rectangle.draw();
}
