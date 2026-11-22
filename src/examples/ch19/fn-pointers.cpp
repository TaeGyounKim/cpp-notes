#include <concepts>
#include <cstddef>
#include <print>
#include <span>
#include <string>
#include <vector>

// 함수 포인터 타입에 별칭을 붙인다.
using Matcher = bool (*)(int, int);
using MatchHandler = void (*)(std::size_t, int, int);

// 고차 함수: 함수를 인수로 받는다.
void compareReadings(std::span<const int> a, std::span<const int> b,
                     Matcher matcher, MatchHandler handler)
{
    if (a.size() != b.size()) { return; }
    for (std::size_t i{ 0 }; i < a.size(); ++i) {
        // 매개변수로 받은 함수 포인터를 보통 함수처럼 부른다.
        if (matcher(a[i], b[i])) { handler(i, a[i], b[i]); }
    }
}

// 같은 일을 하는 제약된 축약 함수 템플릿(권장)
void compareAny(std::span<const int> a, std::span<const int> b,
                std::predicate<int, int> auto matcher,
                std::invocable<std::size_t, int, int> auto handler)
{
    for (std::size_t i{ 0 }; i < a.size() && i < b.size(); ++i) {
        if (matcher(a[i], b[i])) { handler(i, a[i], b[i]); }
    }
}

bool same(int x, int y) { return x == y; }
bool bothHot(int x, int y) { return x >= 30 && y >= 30; }
void report(std::size_t pos, int x, int y)
{
    std::print("[{}: {}, {}] ", pos, x, y);
}

class Sensor
{
public:
    explicit Sensor(std::string room) : m_room{ std::move(room) } {}
    const std::string& room() const { return m_room; }
    int reading() const { return static_cast<int>(m_room.size()); }
    int offset{ 0 };                     // 데이터 멤버 포인터 예시용

private:
    std::string m_room;
};

int main()
{
    std::vector inside{ 21, 30, 25, 33, 18 };
    std::vector outside{ 19, 30, 26, 35, 18 };

    bool (*fun)(int, int){ nullptr };   // 괄호가 없으면 함수 선언이 된다.
    fun = &same;                         // &는 생략해도 된다.
    std::print("같은 값: ");
    compareReadings(inside, outside, fun, report);
    std::print("\n둘 다 30 이상: ");
    compareReadings(inside, outside, bothHot, &report);
    std::print("\n템플릿 판: ");
    compareAny(inside, outside, same, report);
    std::println("");

    // 멤버 함수 포인터: 객체가 있어야 부를 수 있다.
    int (Sensor::*getter)() const{ &Sensor::reading };   // &가 꼭 필요
    Sensor kitchen{ "kitchen" };
    Sensor* ptr{ &kitchen };
    std::println("{} {}", (kitchen.*getter)(), (ptr->*getter)());

    using RoomGetter = const std::string& (Sensor::*)() const;
    RoomGetter roomOf{ &Sensor::room };
    auto alsoReading{ &Sensor::reading };                 // auto가 가장 쉽다.
    std::println("{} {}", (kitchen.*roomOf)(), (kitchen.*alsoReading)());

    // 데이터 멤버 포인터
    int Sensor::*field{ &Sensor::offset };
    kitchen.*field = 5;
    std::println("offset {}", kitchen.offset);
}
