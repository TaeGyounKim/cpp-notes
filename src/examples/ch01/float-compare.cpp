#include <cmath>
#include <print>

int main()
{
    double a{ 0.1 + 0.2 };
    double b{ 0.3 };

    std::println("{}", a == b);

    // 두 값의 차이가 충분히 작으면 같다고 본다.
    // std::abs는 절댓값을 돌려준다.
    double tolerance{ 1e-9 };
    std::println("{}", std::abs(a - b) < tolerance);
}
