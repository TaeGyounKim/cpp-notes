#include <cstdlib>
#include <exception>
#include <iostream>

// noexcept, noexcept 연산자, [[noreturn]], std::_Exit는 모두 C++11부터 있다.
void f1() noexcept {}
void f2() {}

[[noreturn]] void onTerminate()
{
    std::cerr << "잡지 않은 예외! 종료합니다.\n";
    std::_Exit(3);
}

int main()
{
    std::cout << std::boolalpha << noexcept(f1()) << ' ' << noexcept(f2())
              << std::endl;
    std::set_terminate(onTerminate);
    throw 1;   // 아무도 잡지 않는다.
}
