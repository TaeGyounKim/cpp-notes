#include <array>
#include <print>
#include <utility>

struct Point
{
    double x;
    double y;
};

int main()
{
    // 배열에서
    std::array values{ 11, 22, 33 };
    auto [first, second, third]{ values };
    std::println("{} {} {}", first, second, third);

    // 구조체에서
    Point point{ 1.5, 2.5 };
    auto [x, y]{ point };
    std::println("{} {}", x, y);

    // pair에서
    std::pair item{ 4500, 'A' };
    auto [price, grade]{ item };
    std::println("{} {}", price, grade);
}
