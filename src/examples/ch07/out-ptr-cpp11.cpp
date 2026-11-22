#include <iostream>
#include <memory>

typedef int ErrorCode;   // using 별칭도 C++11부터 된다.

ErrorCode create_buffer(int size, int** out)
{
    *out = new int[size]();
    return 0;
}

void destroy_buffer(int* buffer)
{
    std::cout << "버퍼 지움\n";
    delete[] buffer;
}

int main()
{
    std::unique_ptr<int, void (*)(int*)> buffer(nullptr, destroy_buffer);

    // std::out_ptr(C++23) 대신: 맨 포인터로 받은 뒤 곧바로 reset으로 넘긴다.
    int* raw = nullptr;
    if (create_buffer(8, &raw) == 0) {
        buffer.reset(raw);
        raw = nullptr;
        buffer.get()[0] = 42;
        std::cout << "첫 칸: " << buffer.get()[0] << '\n';
    }
}
