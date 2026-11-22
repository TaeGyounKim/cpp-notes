#include <limits>
#include <print>

int main()
{
    std::println("int");
    std::println("  max    : {}", std::numeric_limits<int>::max());
    std::println("  min    : {}", std::numeric_limits<int>::min());
    std::println("  lowest : {}", std::numeric_limits<int>::lowest());

    std::println("double");
    std::println("  max    : {}", std::numeric_limits<double>::max());
    std::println("  min    : {}", std::numeric_limits<double>::min());
    std::println("  lowest : {}", std::numeric_limits<double>::lowest());
}
