#include <cstddef>
#include <iostream>
#include <new>

// bad_alloc, nothrow new, set_new_handler는 C++98부터 있다.
int main()
{
    std::size_t huge = std::size_t(1) << 46;   // int 2의 46제곱 개
    try {
        int* p = new int[huge];
        delete[] p;
    } catch (const std::bad_alloc& e) {
        std::cout << __LINE__ << "번째 줄 근처: " << e.what() << '\n';
    }
    int* q = new (std::nothrow) int[huge];
    std::cout << (q == nullptr ? "nullptr" : "할당됨") << '\n';
    delete[] q;
}
