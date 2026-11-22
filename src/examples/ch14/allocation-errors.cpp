#include <cstddef>
#include <iostream>
#include <new>
#include <print>
#include <source_location>

// new 처리기에서 던질 예외는 bad_alloc이거나 그 파생이어야 한다.
class PleaseTerminate : public std::bad_alloc {};

void onOutOfMemory()
{
    std::println(std::cerr, "메모리 부족: 처리기가 불림");
    throw PleaseTerminate{};
}

int main()
{
    // 실패가 확실하도록 지나치게 큰 크기(int 2의 46제곱 개, 256TiB)를 요청한다.
    std::size_t huge{ std::size_t{ 1 } << 46 };

    // 1. 기본: 실패하면 std::bad_alloc을 던진다.
    try {
        int* p{ new int[huge] };
        delete[] p;
    } catch (const std::bad_alloc& e) {
        auto here{ std::source_location::current() };
        std::println("{}번째 줄: 할당 실패: {}", here.line(), e.what());
    }

    // 2. new(std::nothrow): 실패하면 nullptr을 돌려준다.
    int* q{ new (std::nothrow) int[huge] };
    if (q == nullptr) { std::println("nothrow new: nullptr"); }
    delete[] q;

    // 3. new 처리기: 실패하면 예외 대신 처리기를 부른다.
    std::new_handler old{ std::set_new_handler(onOutOfMemory) };
    try {
        int* r{ new int[huge] };
        delete[] r;
    } catch (const PleaseTerminate&) {
        std::println("처리기가 던진 예외를 잡음");
    }
    std::set_new_handler(old);   // 이전 처리기로 되돌림
}
