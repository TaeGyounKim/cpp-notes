#include <cmath>
#include <map>
#include <print>
#include <random>
#include <string>

// 값별 횟수를 막대로 그린다. 막대 하나의 '#'는 scale번
void draw(const std::map<int, int>& histogram, int scale)
{
    for (const auto& [value, count] : histogram) {
        std::println("{:3} {:6} {}", value, count,
                     std::string(count / scale, '#'));
    }
}

int main()
{
    std::mt19937 engine{ 7 };              // 결과를 재현하려고 고정 씨앗
    const int n{ 100'000 };

    // 균등 분포: 1부터 6까지 모두 비슷하게
    std::uniform_int_distribution<int> die{ 1, 6 };
    std::map<int, int> uniform;
    for (int i{ 0 }; i < n; ++i) { ++uniform[die(engine)]; }
    std::println("균등 분포(주사위)");
    draw(uniform, 1'000);

    // 정규 분포: 평균 10 근처에 몰린다. 실수를 반올림해 센다.
    std::normal_distribution<double> normal{ 10.0, 2.0 };
    std::map<int, int> bell;
    for (int i{ 0 }; i < n; ++i) {
        ++bell[static_cast<int>(std::lround(normal(engine)))];
    }
    // 너무 드문 양 끝은 빼고 그린다.
    std::erase_if(bell, [](const auto& p) {
        return p.first < 4 || p.first > 16;
    });
    std::println("정규 분포(평균 10, 표준 편차 2)");
    draw(bell, 1'000);

    // 이산 분포: 가중치에 비례해 인덱스를 고른다(0: 50%, 1: 30%, 2: 20%).
    std::discrete_distribution<int> pick{ 5, 3, 2 };
    std::map<int, int> weighted;
    for (int i{ 0 }; i < n; ++i) { ++weighted[pick(engine)]; }
    std::println("이산 분포(가중치 5:3:2)");
    draw(weighted, 1'000);

    // 베르누이 분포: 확률 p로 true
    std::bernoulli_distribution coin{ 0.25 };
    int heads{ 0 };
    for (int i{ 0 }; i < n; ++i) { heads += coin(engine); }
    std::println("p = 0.25 -> true {}번 / {}번", heads, n);

    // 실수 균등 분포: [0, 1)
    std::uniform_real_distribution<double> unit{ 0.0, 1.0 };
    std::println("실수 {:.4f}", unit(engine));
}
