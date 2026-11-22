#include <print>

int main()
{
    int temperature{ 31 };

    if (temperature > 30) {
        std::println("덥다");
    } else if (temperature > 15) {
        std::println("적당하다");
    } else {
        std::println("춥다");
    }

    // 조건 자리에 정수를 쓰면 0은 거짓, 0이 아닌 값은 참으로 취급된다.
    int leftover{ 0 };
    if (leftover) {
        std::println("남은 것이 있다");
    } else {
        std::println("남은 것이 없다");
    }
}
