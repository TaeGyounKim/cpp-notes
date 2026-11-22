#include <chrono>
#include <print>

// 프로토타입: 쓰려는 라이브러리 기능만 시험해 보는 작은 프로그램.
// 궁금한 것: <chrono>로 "30일 뒤의 날짜"와 "요일"을 구할 수 있는가?

int main()
{
    using namespace std::chrono;

    const year_month_day start{ 2024y / February / 10d };

    // 날짜에 날 수를 더하려면 sys_days로 바꿔야 한다는 것을 알게 됐다.
    const year_month_day due{ sys_days{ start } + days{ 30 } };
    std::println("대출일: {}", start);
    std::println("반납일: {}", due);

    // 요일도 구할 수 있다.
    const weekday dayOfWeek{ sys_days{ due } };
    std::println("요일: {}", dayOfWeek);

    // 없는 날짜를 만들면 어떻게 되는가?
    const year_month_day invalid{ 2023y / February / 30d };
    std::println("2023-02-30은 유효한가: {}", invalid.ok());
}
