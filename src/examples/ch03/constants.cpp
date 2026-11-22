#include <numbers>
#include <print>

// 매직 넘버: 86400과 3.14159가 무엇인지 읽는 사람이 추측해야 한다.
double badCircleArea(double radius)
{
    return 3.14159 * radius * radius;
}

int badToSeconds(int days)
{
    return days * 86400;
}

// 이름 붙은 상수: 값의 뜻이 이름에 있다.
const int HoursPerDay{ 24 };
const int SecondsPerHour{ 3'600 };

double circleArea(double radius)
{
    return std::numbers::pi * radius * radius;
}

int toSeconds(int days)
{
    return days * HoursPerDay * SecondsPerHour;
}

int main()
{
    std::println("{:.4f} {:.4f}", badCircleArea(2.0), circleArea(2.0));
    std::println("{} {}", badToSeconds(2), toSeconds(2));

    // <numbers>에 미리 정의된 상수들
    std::println("pi    = {}", std::numbers::pi);
    std::println("e     = {}", std::numbers::e);
    std::println("sqrt2 = {}", std::numbers::sqrt2);
    std::println("phi   = {}", std::numbers::phi);
}
