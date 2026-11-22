#include <cstring>
#include <print>

int main()
{
    const char* greeting{ "Hello" };

    // 버그: 글자 5개만큼만 잡았다. 끝의 '\0'을 담을 자리가 없다.
    char* copy{ new char[std::strlen(greeting)] };
    std::strcpy(copy, greeting);   // '\0'이 잡은 칸 밖에 써진다.

    std::println("{}", copy);
    delete[] copy;
}
