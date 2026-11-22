#include <print>

int main()
{
    unsigned int a{ 0b1100 };
    unsigned int b{ 0b1010 };

    // {:04b} 는 "2진수로, 네 자리를 0으로 채워서"라는 뜻
    std::println("a      = {:04b}", a);
    std::println("b      = {:04b}", b);
    std::println("a & b  = {:04b}", a & b);
    std::println("a | b  = {:04b}", a | b);
    std::println("a ^ b  = {:04b}", a ^ b);

    std::println("a << 1 = {:05b} ({})", a << 1, a << 1);
    std::println("a >> 2 = {:04b} ({})", a >> 2, a >> 2);
}
