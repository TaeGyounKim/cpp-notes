#include <print>

int main()
{
    int count{ 100 };

    // while: 조건을 먼저 검사한다. 처음부터 거짓이면 한 번도 실행되지 않는다.
    while (count < 5) {
        std::println("while: {}", count);
        ++count;
    }

    // do/while: 블록을 먼저 실행하고 조건을 나중에 검사한다.
    // 조건이 처음부터 거짓이어도 한 번은 실행된다.
    do {
        std::println("do/while: {}", count);
        ++count;
    } while (count < 5);
}
