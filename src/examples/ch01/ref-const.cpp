#include <print>
#include <string>

std::string makeGreeting()
{
    return "Hello!";
}

int main()
{
    int score{ 80 };
    const int& view{ score };   // 읽기 전용 참조

    // view = 90;               // 오류: const 참조를 거쳐서는 바꿀 수 없다.
    score = 90;                 // 원래 변수로는 바꿀 수 있다.
    std::println("{}", view);   // 같은 것을 보고 있으므로 90

    // 이름 없는 값에는 const 참조만 붙일 수 있다.
    // int& bad{ 5 };           // 오류
    const int& five{ 5 };
    std::println("{}", five);

    // 함수가 돌려준 임시 객체도 마찬가지
    // std::string& bad2{ makeGreeting() };   // 오류
    const std::string& greeting{ makeGreeting() };
    std::println("{}", greeting);
}
