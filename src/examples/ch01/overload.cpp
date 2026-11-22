#include <print>

// 이름은 같고 매개변수가 다른 함수 세 개
int add(int a, int b)
{
    std::println("int 버전");
    return a + b;
}

double add(double a, double b)
{
    std::println("double 버전");
    return a + b;
}

int add(int a, int b, int c)
{
    std::println("int 세 개 버전");
    return a + b + c;
}

int main()
{
    std::println("{}", add(1, 2));
    std::println("{}", add(1.5, 2.25));
    std::println("{}", add(1, 2, 3));
}
