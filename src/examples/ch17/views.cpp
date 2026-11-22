#include <format>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace views = std::views;

int main()
{
    std::vector<int> temps{ 18, 23, 21, 26, 19, 28, 24, 30 };

    // 한 단계씩: 뷰를 만들기만 하고 아직 아무 계산도 하지 않는다.
    auto warm{ temps | views::filter([](int t) { return t >= 21; }) };
    // 섭씨를 절대온도(켈빈, 정수 근삿값)로
    auto kelvin{ warm | views::transform([](int t) { return t + 273; }) };
    auto skipped{ kelvin | views::drop(2) };
    auto reversed{ skipped | views::reverse };
    std::println("21도 이상 {}", warm);
    std::println("켈빈 {}", kelvin);
    std::println("앞 둘 버림 {}", skipped);
    std::println("거꾸로 {}", reversed);

    // 게으른 평가: 원소를 꺼낼 때마다 필요한 만큼만 계산한다.
    auto lazy{ temps
               | views::filter([](int t) {
                     std::print("[검사 {}] ", t);
                     return t >= 21; })
               | views::take(2) };
    std::println("뷰를 만들었다. 이제 훑는다.");
    for (int t : lazy) { std::print("<{}> ", t); }
    std::println("");

    // 뷰를 통해 원본을 고친다(transform 뷰는 읽기 전용이라 안 된다).
    // 단, 고친 값도 filter 조건을 만족해야 한다(아니면 정의되지 않은 동작).
    for (int& t : temps | views::filter([](int t) { return t >= 26; })) {
        t += 1;                                // 26도 이상만 1도 보정
    }
    std::println("고친 원본 {}", temps);

    // 다른 타입으로 바꾸기: 처음 셋을 문자열로
    auto labels{ temps | views::take(3)
                 | views::transform([](int t) {
                       return std::format("{}도", t); }) };
    std::println("{}", labels);
}
