#include <iostream>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

namespace views = std::views;

int main()
{
    // iota: 100부터 끝없이 늘어나는 수. 게으르므로 무한해도 된다.
    auto ids{ views::iota(100)
              | views::filter([](int n) { return n % 7 == 0; })
              | views::take(4) };
    std::println("7의 배수 ID {}", ids);
    std::println("1~5 {}, 반복 {}", views::iota(1, 6), views::repeat('*', 3));

    // istream_view: 표준 입력을 뷰로. 음수가 나오면 멈춘다.
    std::vector<int> readings;
    for (int r : std::ranges::istream_view<int>{ std::cin }
                 | views::take_while([](int r) { return r >= 0; })) {
        readings.push_back(r);
    }
    std::println("읽은 값 {}", readings);

    // C++23 ranges::to: 범위를 컨테이너로
    auto sorted{ std::ranges::to<std::set>(readings) };
    auto halves{ readings
                 | views::transform([](int r) { return r / 2.0; })
                 | std::ranges::to<std::vector<double>>() };
    std::set<int> fromRange{ std::from_range, readings };   // C++23 생성자
    std::println("{} / {} / {}", sorted, halves, fromRange);

    // 문자열을 단어로 쪼개 vector<string>으로
    std::string line{ "거실 부엌 침실" };
    auto words{ line | views::split(' ')
                | views::transform([](auto part) {
                      return std::string{ std::from_range, part }; })
                | std::ranges::to<std::vector>() };
    std::println("{}", words);

    // C++23 컨테이너의 범위 멤버 함수
    std::vector<int> log;
    log.append_range(views::iota(1, 4));
    log.insert_range(log.begin(), views::repeat(0, 2));
    std::println("{}", log);
}
