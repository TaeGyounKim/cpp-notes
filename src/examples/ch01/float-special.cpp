#include <cmath>
#include <limits>
#include <print>

int main()
{
    double zero{ 0.0 };

    double plusInf{ 1.0 / zero };
    double minusInf{ -1.0 / zero };
    double notNumber{ zero / zero };
    std::println("{} {} {}", plusInf, minusInf, notNumber);

    std::println("isinf: {}", std::isinf(plusInf));
    std::println("isnan: {}", std::isnan(notNumber));

    // NaN은 자기 자신과 비교해도 같지 않다.
    std::println("notNumber == notNumber: {}", notNumber == notNumber);

    // 나눗셈 없이 직접 얻는 방법
    double inf{ std::numeric_limits<double>::infinity() };
    double nan{ std::numeric_limits<double>::quiet_NaN() };
    std::println("{} {}", inf, nan);
}
