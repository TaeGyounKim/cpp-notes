#include <cstdlib>
#include <exception>
#include <iostream>
#include <print>
#include <stdexcept>

void f1() noexcept {}
void f2() noexcept(false) {}
void f3() noexcept(noexcept(f1())) {}   // f1()이 noexcept면 noexcept
void f4() noexcept(noexcept(f2())) {}

// 잡지 않은 예외가 나면 불린다. 반드시 프로그램을 끝내야 한다.
[[noreturn]] void onTerminate()
{
    std::println(std::cerr, "잡지 않은 예외! 종료합니다.");
    std::cout.flush();                 // _Exit는 버퍼를 비우지 않는다.
    std::_Exit(3);
}

void process(int value) noexcept
{
    if (value < 0) {
        // noexcept 함수에서 던지면 잡을 기회 없이 terminate()가 불린다.
        throw std::invalid_argument{ "음수" };
    }
    std::println("처리 {}", value);
}

int main()
{
    // noexcept 연산자: 컴파일할 때 식이 예외를 던지지 않는지 묻는다.
    std::println("{} {} {} {}", noexcept(f1()), noexcept(f2()),
                 noexcept(f3()), noexcept(f4()));

    std::set_terminate(onTerminate);
    process(1);
    try {
        process(-1);                   // try가 있어도 잡지 못한다.
    } catch (...) {
        std::println("여기에 오지 않는다");
    }
}
