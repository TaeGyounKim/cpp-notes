#include <format>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// 일련번호로 장치를 찾는 등록부. 키는 값 객체의 한 필드다.
class Device
{
public:
    Device(int serial, std::string room)
        : m_serial{ serial }, m_room{ std::move(room) } {}
    int serial() const { return m_serial; }
    const std::string& room() const { return m_room; }
    void moveTo(std::string room) { m_room = std::move(room); }

private:
    int m_serial;
    std::string m_room;
};

class Registry
{
public:
    bool add(const Device& d)
    {
        return m_devices.emplace(d.serial(), d).second;   // 새로 넣었는지
    }
    void remove(int serial) { m_devices.erase(serial); }

    Device& find(int serial)
    {
        auto it{ m_devices.find(serial) };
        if (it == m_devices.end()) {
            throw std::out_of_range{ std::format("{}번 장치 없음", serial) };
        }
        return it->second;
    }

private:
    std::map<int, Device> m_devices;
};

int main()
{
    Registry reg;
    reg.add(Device{ 100, "거실" });
    reg.add(Device{ 200, "부엌" });
    std::println("같은 번호 다시 등록? {}", reg.add(Device{ 100, "침실" }));
    reg.find(100).moveTo("서재");               // 참조로 받아 바로 고침
    std::println("100번은 {}", reg.find(100).room());
    try {
        reg.find(300);
    } catch (const std::out_of_range& e) {
        std::println("{}", e.what());
    }

    // multimap: 같은 키(날짜)에 여러 일정
    std::multimap<std::string, std::string> schedule{
        { "월", "필터 교체" }, { "화", "점검" }, { "월", "배터리 확인" } };
    schedule.insert({ "월", "청소" });           // 언제나 성공. 반복자를 돌려줌
    auto [first, last]{ schedule.equal_range("월") };
    for (auto it{ first }; it != last; ++it) { std::print("{} ", it->second); }
    std::println("(월요일 {}건)", schedule.count("월"));
    auto mondays{ std::ranges::subrange{ first, last } | std::views::values
                  | std::ranges::to<std::vector>() };   // C++23
    std::println("{}", mondays);
    std::println("lower_bound(수) == upper_bound(수)? {}",
                 schedule.lower_bound("수") == schedule.upper_bound("수"));

    // set: 값이 곧 키. 중복 없이 정렬
    std::set<std::string> allowed{ "민수", "지은" };
    allowed.insert("하늘");
    allowed.insert("민수");                      // 이미 있어 무시
    allowed.erase("지은");
    std::println("허용 {} / 지은 허용? {}", allowed, allowed.contains("지은"));
    // *allowed.begin() = "x";                  // 오류: 원소는 const

    // multiset: 중복 허용
    std::multiset<int> ratings{ 5, 3, 5, 4, 5 };
    std::println("{} / 5점 {}개", ratings, ratings.count(5));
}
