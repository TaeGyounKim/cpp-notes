#include <print>

int main()
{
    // 1. 10진 소수는 대부분 정확히 담기지 않는다.
    //    (== 는 두 값이 같은지 묻는 연산자)
    double sum{ 0.1 + 0.2 };
    std::println("0.1 + 0.2 = {}", sum);
    std::println("0.3과 같은가? {}", sum == 0.3);

    // 2. 크기가 크게 다른 두 수를 더하면 작은 쪽이 사라진다.
    double huge{ 1e20 };   // 1 뒤에 0이 20개
    std::println("1을 더해도 그대로인가? {}", huge + 1.0 == huge);

    // 3. 거의 같은 두 수를 빼면 믿을 수 있는 자릿수가 줄어든다.
    double x{ 1.000'000'1 };
    double y{ 1.000'000'0 };
    std::println("x - y = {}", x - y);
}
