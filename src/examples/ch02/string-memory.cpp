#include <print>
#include <string>

int main()
{
    std::string text{ "hello" };
    text += ", there";            // 길어져도 메모리는 알아서 늘어난다.

    std::string other{ text };    // 복사본. 서로 다른 문자열이다.
    if (text == other) {
        other[0] = 'H';           // [ ]로 글자 하나를 읽고 바꾼다.
    }
    std::println("{}", text);
    std::println("{}", other);

    // 글자를 계속 붙이면 마련해 둔 공간(capacity)이 단계적으로 커진다.
    std::string grow;
    std::println("size {} / capacity {}", grow.size(), grow.capacity());
    for (int i{ 0 }; i < 40; ++i) {
        grow += 'x';
    }
    std::println("size {} / capacity {}", grow.size(), grow.capacity());
}   // text, other, grow가 쓰던 메모리는 여기서 자동으로 돌려진다.
