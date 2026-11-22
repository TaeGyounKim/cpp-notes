#include <print>

int main()
{
    int count{ 42 };

    // 번호를 생략하면 인수가 차례대로 들어간다.
    std::println("Read {} bytes from {}", count, "notes.txt");

    // 번호를 적으면 몇 번째 인수인지 직접 고른다. 0부터 센다.
    std::println("Read {0} bytes from {1}", count, "notes.txt");

    // 순서를 바꿀 수 있다. 인수의 순서는 그대로 둔 채로.
    std::println("{1}에서 {0}바이트를 읽음", count, "notes.txt");

    // 같은 인수를 여러 번 쓸 수 있다.
    std::println("{0} + {0} = {1}", count, count + count);

    // 번호가 있는 것과 없는 것을 섞어 쓸 수 없다.
    // std::println("{0} bytes from {}", count, "a");   // 오류
}
