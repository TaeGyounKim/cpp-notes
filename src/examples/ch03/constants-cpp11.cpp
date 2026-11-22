#include <iostream>

// <numbers>(C++20)가 없으면 상수를 직접 정의한다.
const double Pi{ 3.14159265358979323846 };

// 자릿수 구분 기호 '(C++14)가 없으면 붙여 쓴다.
const int HoursPerDay{ 24 };
const int SecondsPerHour{ 3600 };

double circleArea(double radius)
{
    return Pi * radius * radius;
}

int main()
{
    std::cout << circleArea(2.0) << '\n';
    std::cout << 2 * HoursPerDay * SecondsPerHour << '\n';
}
