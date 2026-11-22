#include <algorithm>
#include <functional>
#include <list>
#include <print>
#include <ranges>
#include <string>
#include <vector>

class Sensor
{
public:
    Sensor(std::string room, double celsius)
        : m_room{ std::move(room) }, m_celsius{ celsius } {}
    const std::string& room() const { return m_room; }
    double celsius() const { return m_celsius; }

private:
    std::string m_room;
    double m_celsius;
};

int main()
{
    // 범위를 통째로 넘긴다. 시작·끝 반복자를 잘못 짝지을 일이 없다.
    std::vector<int> data{ 33, 11, 22 };
    std::ranges::sort(data);
    int raw[]{ 5, 4, 6 };                     // C 배열도 범위
    std::println("{} / 크기 {} / 비었나? {}", data, std::ranges::size(raw),
                 std::ranges::empty(raw));

    std::vector<Sensor> sensors{ { "침실", 19.5 }, { "거실", 22.0 },
                                 { "부엌", 24.5 } };

    // Sensor에는 operator<가 없다. 프로젝션으로 비교할 값을 꺼낸다.
    std::ranges::sort(sensors, {}, &Sensor::room);       // 기본 비교 {}
    for (const auto& s : sensors) { std::print("{} ", s.room()); }
    std::println("");

    // 비교자와 프로젝션을 함께: 온도 내림차순
    std::ranges::sort(sensors, std::ranges::greater{},
                      [](const Sensor& s) { return s.celsius(); });
    std::println("가장 따뜻한 곳 {}", sensors.front().room());

    // 찾기에도 프로젝션: 방 이름이 "거실"인 센서
    auto it{ std::ranges::find(sensors, "거실", &Sensor::room) };
    if (it != sensors.end()) { std::println("거실 {}도", it->celsius()); }

    std::list<int> linked{ 3, 1, 2 };
    // std::ranges::sort(linked);   // 오류: list는 random_access_range가 아님
    linked.sort();                  // list는 멤버 sort()
    std::println("{}", linked);
}
