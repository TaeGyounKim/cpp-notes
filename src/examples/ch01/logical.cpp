#include <print>

int main()
{
    int age{ 25 };
    bool member{ false };

    std::println("{}", age >= 19);            // 크거나 같다
    std::println("{}", age == 25);            // 같다 (= 하나는 대입!)
    std::println("{}", age != 25);            // 같지 않다
    std::println("{}", !member);              // NOT: 뒤집기
    std::println("{}", age >= 19 && member);  // AND: 둘 다 참이어야 참
    std::println("{}", age >= 19 || member);  // OR: 하나만 참이어도 참

    // 단락 평가: 앞에서 결과가 정해지면 뒤는 계산하지 않는다.
    int total{ 100 };
    int count{ 0 };
    // count가 0이면 && 뒤의 나눗셈은 실행되지 않으므로 안전하다.
    if (count != 0 && total / count > 10) {
        std::println("평균이 10보다 크다");
    } else {
        std::println("셀 것이 없거나 평균이 10 이하");
    }
}
