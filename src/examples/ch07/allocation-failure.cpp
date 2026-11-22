#include <cstddef>
#include <limits>
#include <new>
#include <print>

int main()
{
    // 일부러 감당할 수 없을 만큼 큰 크기를 요청한다.
    std::size_t huge{ std::numeric_limits<std::size_t>::max() / 2 };

    // 기본 new: 실패하면 예외를 던진다.
    try {
        char* buffer{ new char[huge] };
        delete[] buffer;
    } catch (const std::bad_alloc& error) {
        std::println("new 실패, 예외: {}", error.what());
    }

    // nothrow new: 실패하면 nullptr을 돌려준다. 검사를 잊기 쉽다.
    char* buffer{ new (std::nothrow) char[huge] };
    if (buffer == nullptr) {
        std::println("nothrow new 실패, nullptr");
    }
    delete[] buffer;   // nullptr에 delete[]는 아무 일도 하지 않는다.
}
