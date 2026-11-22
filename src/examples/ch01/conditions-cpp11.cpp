#include <iostream>

enum class Shipping { Standard, Express, Overnight };

int main()
{
    int price{ 4500 };
    int count{ 3 };

    // if 문의 초기화 구문 대신: 블록으로 감싸 변수의 범위를 좁힌다.
    {
        int total{ price * count };
        if (total >= 10000) {
            std::cout << total << ": free shipping\n";
        } else {
            std::cout << total << ": shipping fee added\n";
        }
    }

    // using enum과 [[fallthrough]] 대신:
    // 전부 Shipping:: 를 붙이고, 이어 가는 곳은 주석으로 알린다.
    Shipping shipping{ Shipping::Overnight };
    int fee{ 3000 };
    switch (shipping) {
        case Shipping::Overnight:
            fee += 5000;
            // fallthrough
        case Shipping::Express:
            fee += 2000;
            break;
        case Shipping::Standard:
            break;
    }
    std::cout << fee << '\n';

    // <=> 대신: 비교 연산자를 하나씩 쓴다.
    int a{ 11 };
    int b{ 20 };
    if (a < b) { std::cout << "less\n"; }
    else if (a > b) { std::cout << "greater\n"; }
    else { std::cout << "equal\n"; }
}
