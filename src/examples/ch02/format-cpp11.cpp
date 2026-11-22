#include <cstdio>
#include <iostream>

int main()
{
    int width{ 1920 };
    int height{ 1080 };

    // 방법 1: C 스타일 printf. 형식 문자열과 인수가 나뉘어 읽기 쉽지만
    // 형식 지정(%d)과 인수의 타입이 맞는지 직접 챙겨야 한다.
    std::printf("%d x %d\n", width, height);

    // 방법 2: I/O 스트림. 타입은 안전하지만 문장과 값이 뒤섞인다.
    std::cout << width << " x " << height << '\n';
}
