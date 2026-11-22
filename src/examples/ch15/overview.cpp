#include <print>

struct Vec2
{
    double x{ 0 };
    double y{ 0 };

    // 왼쪽이 Vec2인 연산자는 멤버로. 객체를 바꾸지 않으면 const
    Vec2 operator-() const { return Vec2{ -x, -y }; }

    // 대입 계열은 *this의 참조를 돌려준다(a += b += c 가능).
    Vec2& operator+=(const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

// 새 객체를 만드는 연산자는 값으로 돌려준다.
Vec2 operator+(Vec2 lhs, const Vec2& rhs) { return lhs += rhs; }

// 왼쪽이 double이어야 하는 연산자는 전역 함수로만 가능하다.
Vec2 operator*(double k, const Vec2& v) { return Vec2{ k * v.x, k * v.y }; }
Vec2 operator*(const Vec2& v, double k) { return k * v; }

// ^를 "거듭제곱"으로 쓰면 우선순위가 덧셈보다 낮다는 함정이 있다.
double operator^(const Vec2& v, int) { return v.x * v.x + v.y * v.y; }

// &&를 오버로드하면 단락 평가가 사라진다.
struct Flag
{
    bool on{ false };
};
bool operator&&(const Flag& a, const Flag& b) { return a.on && b.on; }

Flag loud(bool on, const char* name)
{
    std::println("  {} 계산됨", name);
    return Flag{ on };
}

int main()
{
    Vec2 a{ 1, 2 };
    Vec2 b{ 3, 4 };
    Vec2 c{ a + b };
    Vec2 d{ 2 * a };          // 전역 operator*(double, const Vec2&)
    Vec2 e{ -a };
    std::println("c=({}, {}) d=({}, {}) e=({}, {})", c.x, c.y, d.x, d.y,
                 e.x, e.y);

    double r{ (a ^ 2) + 1 };  // 괄호가 필요하다.
    std::println("|a|^2 + 1 = {}", r);

    std::println("기본 bool의 && :");
    bool shortCircuit{ false && (std::println("  오른쪽 계산됨"), true) };
    std::println("  결과 {}", shortCircuit);

    std::println("오버로드한 && :");
    bool both{ loud(false, "왼쪽") && loud(true, "오른쪽") };
    std::println("  결과 {}", both);

    int n{ 1 };
    std::println("쉼표 연산자: {}", (++n, 2 * n));   // n을 늘린 뒤 2 * n
}
