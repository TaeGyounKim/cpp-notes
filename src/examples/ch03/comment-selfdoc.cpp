#include <print>

// 뜻이 바로 드러나지 않는 식에 이름을 붙인다.
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInFebruary(int year)
{
    return isLeapYear(year) ? 29 : 28;
}

int main()
{
    const int year{ 2024 };

    // 주석 없이도 읽힌다.
    if (isLeapYear(year)) {
        std::println("{}년은 윤년", year);
    }
    std::println("2월은 {}일", daysInFebruary(year));
    std::println("1900년 2월은 {}일", daysInFebruary(1900));
}
