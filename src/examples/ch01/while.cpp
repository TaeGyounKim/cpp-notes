#include <print>

int main()
{
    // 조건이 참인 동안 블록을 되풀이한다.
    int count{ 3 };
    while (count > 0) {
        std::println("{}", count);
        --count;
    }
    std::println("발사!");

    // break: 반복문을 즉시 빠져나간다.
    // continue: 이번 바퀴의 남은 부분을 건너뛰고 조건 검사로 돌아간다.
    int number{ 0 };
    while (true) {
        ++number;
        if (number == 3) {
            continue;   // 3은 출력하지 않고 다음 바퀴로
        }
        if (number > 5) {
            break;      // 5를 넘으면 끝
        }
        std::println("number = {}", number);
    }
}
