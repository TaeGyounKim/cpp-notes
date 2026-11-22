// C++20: std::format으로 형식을 지정한다.
#include <format>
#include <iostream>

int main()
{
    std::cout << std::format("{:<8}{:>5}{:>9}\n", "item", "qty", "price");
    std::cout << std::format("{:<8}{:>5}{:>9.2f}\n", "apple", 3, 1.5);
    std::cout << std::format("{:<8}{:>5}{:>9.2f}\n", "melon", 12, 23.456);
    std::cout << std::format("order no. {:05}\n", 42);
}
