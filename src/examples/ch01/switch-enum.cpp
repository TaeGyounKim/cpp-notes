#include <print>

enum class Shipping { Standard, Express, Overnight };

int main()
{
    Shipping shipping{ Shipping::Overnight };
    int fee{ 3000 };

    switch (shipping) {
        using enum Shipping;   // 이 switch 문 안에서만 Shipping:: 생략

        case Overnight:
            fee += 5000;
            [[fallthrough]];   // 일부러 아래 case로 이어 간다는 표시
        case Express:
            fee += 2000;
            break;
        case Standard:
            break;
    }

    std::println("배송비: {}원", fee);
}
