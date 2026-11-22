#include <print>

void f()
{
    int i{ 7 };
    int* ptr{ new int };
    *ptr = 8;
    int** handle{ new int* };
    *handle = new int{ 9 };
    std::println("{} {} {}", i, *ptr, **handle);
    delete ptr;
    ptr = nullptr;
}   // handle이 가리키던 두 칸은 아무도 해제하지 않았다.

int main()
{
    f();
}
