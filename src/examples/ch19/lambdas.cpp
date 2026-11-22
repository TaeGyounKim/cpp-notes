#include <algorithm>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

// std::function은 콜백을 데이터 멤버로 저장할 때 빛난다.
class Thermostat
{
public:
    using Alarm = std::function<void(int)>;
    void onOverheat(Alarm alarm) { m_alarm = std::move(alarm); }
    void report(int celsius) const
    {
        if (celsius > 28 && m_alarm) { m_alarm(celsius); }   // 비었는지 확인
    }

private:
    Alarm m_alarm;
};

class Room
{
public:
    explicit Room(std::string name) : m_name{ std::move(name) } {}
    auto greeter() const
    {
        return [this] { std::println("{}입니다", m_name); };   // this 캡처
    }

private:
    std::string m_name;
};

int main()
{
    auto hello{ [] { std::println("람다 안녕"); } };   // () 생략 가능
    hello();
    auto add{ [](int a, int b) -> int { return a + b; } };   // 반환 타입 명시
    std::println("합 {}", add(11, 22));

    int limit{ 25 };
    int alarms{ 0 };
    auto isHot{ [limit](int t) { return t > limit; } };      // 값으로 캡처
    auto ring{ [&alarms](int t) {                             // 참조로 캡처
        ++alarms;
        std::println("경보: {}도", t);
    } };
    limit = 30;                                  // 복사본에는 영향 없음
    std::println("28은 뜨거운가? {}", isHot(28));

    int calls{ 0 };
    auto counter{ [calls]() mutable { return ++calls; } };   // 복사본을 고침
    counter();
    std::println("counter {} / 원본 calls {}", counter(), calls);

    Thermostat t;
    t.onOverheat(ring);                          // 람다를 std::function에 저장
    t.report(27);
    t.report(31);
    t.onOverheat([](int c) { std::println("다른 경보 {}", c); });
    t.report(35);
    std::println("울린 경보 {}번", alarms);

    Room living{ "거실" };
    living.greeter()();

    // 캡처가 없는 람다는 함수 포인터로 바뀐다.
    int (*twice)(int){ [](int x) { return x * 2; } };
    std::println("twice {}", twice(21));

    // 이동만 되는 콜백은 move_only_function으로(C++23)
    auto data{ std::make_unique<int>(7) };
    std::move_only_function<int() const> reader{
        [d = std::move(data)] { return *d; } };   // 4편: 캡처 표현식
    std::println("reader {}", reader());

    std::vector temps{ 22, 31, 19, 29 };
    auto n{ std::ranges::count_if(temps, isHot) };
    std::println("25도 넘는 날 {}일", n);
}
