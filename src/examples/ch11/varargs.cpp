#include <cstdarg>
#include <cstdio>
#include <print>

bool g_verbose{ true };

// printf처럼 서식 문자열 뒤에 개수·타입이 정해지지 않은 인수를 받는다.
void logLine(const char* format, ...)
{
    if (!g_verbose) { return; }
    va_list args;
    va_start(args, format);       // 마지막 이름 있는 매개변수를 넘긴다.
    std::vprintf(format, args);   // 인수 목록을 통째로 넘긴다.
    va_end(args);                 // va_start 뒤에는 반드시 va_end
}

// 인수를 직접 꺼낸다. 개수는 호출하는 쪽이 첫 인수로 알려 준다.
int sumInts(int count, ...)
{
    va_list args;
    va_start(args, count);
    int total{ 0 };
    for (int i{ 0 }; i < count; ++i) {
        total += va_arg(args, int);   // 타입도 믿고 꺼낼 뿐이다.
    }
    va_end(args);
    return total;
}

int main()
{
    logLine("온도 %d도\n", 23);
    logLine("%s 센서, 습도 %d%%\n", "거실", 41);
    std::println("합계 {}", sumInts(4, 10, 20, 30, 40));
    std::println("합계 {}", sumInts(2, 5, 6));
}
