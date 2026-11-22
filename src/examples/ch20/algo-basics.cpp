#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <span>
#include <vector>

// 조건자 함수
bool isFever(double t) { return t >= 37.5; }

double mean(std::span<const double> v)
{
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();   // 시작값 0.0
}

double geometricMean(std::span<const int> v)
{
    int product{ std::accumulate(v.begin(), v.end(), 1, std::multiplies<>{}) };
    return std::pow(product, 1.0 / v.size());
}

int main()
{
    // 입력: 체온들을 읽고 0이 나오면 멈춘다.
    std::vector<double> temps;
    for (double t; std::cin >> t && t != 0;) { temps.push_back(t); }

    // find: 값이 같은 첫 원소. 못 찾으면 넘겨준 끝 반복자
    if (auto it{ std::find(temps.cbegin(), temps.cend(), 36.5) };
        it == temps.cend()) {
        std::println("36.5 없음");
    } else {
        std::println("36.5는 {}번째", it - temps.cbegin());
    }

    // 일부 범위만 찾을 수도 있다: 처음 두 개
    auto end2{ temps.cbegin() + 2 };
    bool inFirstTwo{ std::find(temps.cbegin(), end2, 38.2) != end2 };
    std::println("앞 둘에 38.2? {}", inFirstTwo);

    // find_if: 조건자를 만족하는 첫 원소(함수, 람다 모두 됨)
    if (auto it{ std::find_if(temps.cbegin(), temps.cend(), isFever) };
        it != temps.cend()) {
        std::println("첫 발열 {}", *it);
    }

    std::println("평균 {:.2f}, 기하 평균 {:.2f}", mean(temps),
                 geometricMean(std::vector{ 2, 8 }));

    // 알고리즘은 콜백을 복사할 수 있다. 상태를 세려면 std::ref로
    auto counted{ [n = 0](double t) mutable {
        ++n;
        std::print("[{}번째 검사] ", n);
        return t >= 37.5;
    } };
    auto found{ std::find_if(temps.cbegin(), temps.cend(), std::ref(counted)) };
    counted(0.0);                               // ref였으므로 이어서 센다.
    std::println("\n찾은 값 {}", *found);
}
