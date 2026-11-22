#include <algorithm>
#include <iostream>
#include <print>
#include <stdexcept>
#include <vector>

int main()
{
    // 개수를 모르는 점수를 읽어 최고점이 100이 되게 맞춘다.
    std::vector<double> scores;                 // 원소 0개
    double value;
    while (std::cin >> value && value >= 0) {
        scores.push_back(value);                // 끝에 넣으면 알아서 커진다.
    }
    if (scores.empty()) { return 0; }
    double top{ *std::ranges::max_element(scores) };
    for (auto& s : scores) { s = s / top * 100; }      // auto&로 고친다.
    std::println("맞춘 점수 {} (원소 {}개)", scores, scores.size());
    std::println("처음 {} 마지막 {}", scores.front(), scores.back());

    try {
        std::println("{}", scores.at(scores.size()));   // 범위 검사
    } catch (const std::out_of_range&) {
        std::println("at()이 예외를 던짐");
    }

    // 소괄호와 중괄호의 차이
    std::vector<int> a(3, 7);                   // 7이 3개
    std::vector<int> b{ 3, 7 };                 // 원소 3과 7
    std::vector c{ 1, 2, 3 };                   // 클래스 템플릿 인수 추론
    std::println("a {} b {} c {}", a, b, c);

    // 다시 채우기, 맞바꾸기
    a.assign(2, 0);                             // 0이 2개로 바뀜
    b.assign({ 9, 8, 7 });
    a.swap(b);                                  // 상수 시간
    std::println("a {} b {}", a, b);

    // 사전식 비교
    std::vector<int> x{ 1, 2, 3 };
    std::vector<int> y{ 1, 2, 4 };
    std::vector<int> z{ 1, 2 };
    std::println("x == y? {} x < y? {} z < x? {}", x == y, x < y, z < x);
    std::println("{:n}", x);                    // 대괄호 없이
}
