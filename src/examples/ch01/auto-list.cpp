#include <initializer_list>
#include <print>

int main()
{
    // 등호가 있으면: std::initializer_list<int>
    auto a = { 11 };
    auto b = { 11, 22 };
    std::println("{} {}", a.size(), b.size());

    // 등호가 없으면: 값 하나의 타입
    auto c{ 11 };   // int
    std::println("{}", c + 1);

    // auto d{ 11, 22 };       // 오류: 값이 둘 이상이면 안 된다.
    // auto e = { 11, 22.5 };  // 오류: 타입이 섞여 있다.
}
