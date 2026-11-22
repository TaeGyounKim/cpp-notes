#include <print>

enum class Direction { Up, Down, Left, Right };                 // 기반 타입: int
enum class TinyDirection : unsigned char { Up, Down, Left, Right };

int main()
{
    // sizeof(타입)은 그 타입의 값 하나가 차지하는 바이트 수
    std::println("Direction     : {}바이트", sizeof(Direction));
    std::println("TinyDirection : {}바이트", sizeof(TinyDirection));
}
