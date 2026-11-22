#include <map>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace views = std::views;

int main()
{
    std::vector<std::string> rooms{ "거실", "부엌", "침실" };
    std::vector<double> temps{ 22.0, 24.5, 19.5, 20.0 };

    // C++23: 여러 범위를 나란히(짧은 쪽에 맞춤), 위치와 함께
    std::println("zip {}", views::zip(rooms, temps));
    for (auto [i, room] : views::enumerate(rooms)) {
        std::print("{}:{} ", i, room);
    }
    std::println("");

    // C++23: 이웃끼리 묶기, 덩어리로 나누기, 건너뛰기
    std::vector<int> v{ 1, 3, 6, 10, 15 };
    std::println("adjacent<2> {}", v | views::adjacent<2>);
    auto diff{ [](int a, int b) { return b - a; } };
    std::println("이웃 차 {}", v | views::pairwise_transform(diff));
    std::println("chunk(2) {}", v | views::chunk(2));
    std::println("stride(2) {}", v | views::stride(2));

    // 쪼개고 다시 잇기
    std::string_view csv{ "21.5,22.0,23.5" };
    for (auto part : csv | views::split(',')) {
        std::print("[{}] ", std::string_view{ part });
    }
    std::println("");
    std::println("{}", rooms | views::join_with(std::string_view{ " / " })
                           | std::ranges::to<std::string>());   // 5편

    // map의 키와 값만 보기(C++20)
    std::map<std::string, int> limits{ { "온도", 30 }, { "습도", 60 } };
    std::println("keys {} values {}", limits | views::keys,
                 limits | views::values);

    // C++23: 모든 조합
    std::vector<int> a{ 0, 1 };
    std::println("{}", views::cartesian_product(a, a));
}
