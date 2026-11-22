#include <cstdlib>
#include <print>

// 이 함수는 호출한 곳으로 절대 돌아가지 않는다.
[[noreturn]] void stopProgram()
{
    std::println("계속할 수 없어 프로그램을 끝냅니다.");
    std::exit(1);   // 프로그램을 종료 코드 1로 즉시 끝낸다. <cstdlib>
}

int safeDivide(int total, int count)
{
    if (count == 0) {
        stopProgram();
        // 여기에는 return이 없다. 그래도 경고가 나지 않는다.
    } else {
        return total / count;
    }
}

int main()
{
    std::println("{}", safeDivide(100, 4));
    std::println("{}", safeDivide(100, 0));
    std::println("이 줄은 출력되지 않는다.");
}
