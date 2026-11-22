#include <print>
#include <stdexcept>

int average(int total, int count)
{
    if (count == 0) {
        // 계속할 수 없는 상황을 알린다. 함수는 여기서 즉시 끝난다.
        throw std::invalid_argument{ "count는 0일 수 없습니다." };
    }
    return total / count;
}

int main()
{
    try {
        std::println("{}", average(100, 4));
        std::println("{}", average(100, 0));   // 여기서 예외가 던져진다.
        std::println("{}", average(90, 3));    // 실행되지 않는다.
    } catch (const std::invalid_argument& exception) {
        std::println("예외를 잡음: {}", exception.what());
    }

    std::println("프로그램은 계속 실행된다.");
}
