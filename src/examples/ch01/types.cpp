#include <print>

int main()
{
    int i{ -7 };
    short s{ 13 };
    long l{ -7L };
    long long ll{ 14LL };
    unsigned int u{ 2U };
    float f{ 7.2f };
    double d{ 7.2 };
    char ch{ 'm' };
    bool b{ true };

    std::println("{} {} {} {} {}", i, s, l, ll, u);
    std::println("{} {} {} {}", f, d, ch, b);
}
