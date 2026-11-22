#include <ctime>
#include <iostream>

// 달력 타입과 시간대(C++20)가 없으므로 C의 std::tm과 std::mktime을 쓴다.
// mktime은 범위를 넘은 필드(예: 12월 65일)를 맞는 날짜로 정규화한다.
// 지역 시각 기준이므로 일광 절약 시간을 피하려고 정오로 둔다.
int main()
{
    std::tm date = {};
    date.tm_year = 2026 - 1900;    // 1900년부터의 연
    date.tm_mon = 12 - 1;          // 0부터 시작하는 월
    date.tm_mday = 20 + 45;        // 45일 뒤
    date.tm_hour = 12;
    date.tm_isdst = -1;
    std::mktime(&date);

    const char* names[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    char buf[32];
    std::strftime(buf, sizeof buf, "%Y-%m-%d", &date);
    std::cout << buf << ' ' << names[date.tm_wday] << '\n';

    int y = 2028;
    bool leap = (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    std::cout << y << " leap? " << std::boolalpha << leap << '\n';
}
