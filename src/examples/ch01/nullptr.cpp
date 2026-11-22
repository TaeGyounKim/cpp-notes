#include <cstddef>   // NULL
#include <print>

void show(int value)
{
    std::println("int 버전: {}", value);
}

void show(int* pointer)
{
    if (pointer == nullptr) {
        std::println("포인터 버전: 널 포인터");
    }
}

int main()
{
    show(0);         // 0은 정수이므로 int 버전
    show(nullptr);   // nullptr은 포인터이므로 포인터 버전

    // show(NULL);   // 오류: 정수로도 포인터로도 읽을 수 있어 모호하다.
}
