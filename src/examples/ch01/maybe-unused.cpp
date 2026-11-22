#include <print>

// width는 쓰지만 height는 아직 쓰지 않는다.
// [[maybe_unused]]가 붙은 height는 경고가 나지 않고, depth만 경고가 난다.
int area(int width, [[maybe_unused]] int height, int depth)
{
    return width * 10;
}

int main()
{
    std::println("{}", area(3, 4, 5));
}
