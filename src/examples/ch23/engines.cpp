#include <algorithm>
#include <functional>
#include <print>
#include <random>
#include <vector>

// 엔진을 참조로 받아야 호출할 때마다 엔진의 상태가 이어진다.
std::vector<int> rollDice(std::mt19937& engine, int count)
{
    std::uniform_int_distribution<int> die{ 1, 6 };
    std::vector<int> rolls(count);
    std::ranges::generate(rolls, [&] { return die(engine); });
    return rolls;
}

int main()
{
    // random_device: (가능하면) 하드웨어의 진짜 난수. 느리므로 씨앗용
    std::random_device seeder;
    std::println("entropy {}, 범위 [{}, {}]", seeder.entropy(), seeder.min(),
                 seeder.max());

    // 의사 난수 엔진에 씨앗을 준다.
    std::mt19937 engine{ seeder() };
    std::println("주사위 {}", rollDice(engine, 10));
    std::println("주사위 {}", rollDice(engine, 10));   // 이어서 다른 값

    // 같은 씨앗이면 같은 순서열: 테스트나 재현에 쓴다.
    // (함수 인수의 평가 순서는 정해지지 않으므로 한 문장에 하나씩 꺼낸다.)
    std::mt19937 a{ 2026 };
    std::mt19937 b{ 2026 };
    auto a1{ a() };
    auto a2{ a() };
    auto b1{ b() };
    auto b2{ b() };
    std::println("같은 씨앗 {} {} / {} {}", a1, a2, b1, b2);

    // bind는 엔진을 "복사"한다. 원래 engine은 진행되지 않는다.
    std::uniform_int_distribution<int> pct{ 1, 100 };
    auto copied{ std::bind(pct, engine) };
    int c1{ copied() };
    int c2{ copied() };
    int e1{ pct(engine) };
    int e2{ pct(engine) };
    std::println("복사본 {} {} / 원본 {} {}", c1, c2, e1, e2);
    auto byRef{ std::bind(pct, std::ref(engine)) };    // 참조로 묶기
    std::println("참조 {}", byRef());

    // 엔진은 [min(), max()] 범위의 부호 없는 정수를 낸다.
    std::println("mt19937 [{}, {}], 첫 값 {}", std::mt19937::min(),
                 std::mt19937::max(), std::mt19937{}());
}
