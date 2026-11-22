#include <format>
#include <iomanip>
#include <iostream>
#include <print>
#include <span>
#include <spanstream>
#include <sstream>
#include <string>
#include <utility>

class Reading
{
public:
    Reading() = default;
    Reading(std::string place, double value, bool alarm)
        : m_place{ std::move(place) }, m_value{ value }, m_alarm{ alarm } {}
    const std::string& place() const { return m_place; }
    double value() const { return m_value; }
    bool alarm() const { return m_alarm; }

private:
    std::string m_place;
    double m_value{ 0 };
    bool m_alarm{ false };
};

// println으로 Reading을 출력하게 하는 사용자 정의 formatter(서식 지정자 없음)
template <>
struct std::formatter<Reading>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Reading& r, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{} {}도{}", r.place(), r.value(),
                              r.alarm() ? " (경보)" : "");
    }
};

// 매개변수 없는 사용자 정의 조작자
std::ostream& bullet(std::ostream& out) { return out << " - "; }

// 문자열 스트림에서 Reading 하나를 읽는다. 형식: "장소" 값 true|false
Reading parseReading(std::istringstream& in)
{
    std::string place;
    double value{ 0 };
    bool alarm{ false };
    in >> std::quoted(place) >> value >> std::boolalpha >> alarm;
    if (in) { return Reading{ place, value, alarm }; }
    return Reading{};
}

int main()
{
    Reading r{ "거실", 23.5, false };
    std::println("측정: {}", r);
    std::cout << "목록" << bullet << "첫째" << bullet << "둘째\n";

    // ostringstream으로 문자열을 쌓는다.
    std::ostringstream out;
    bool first{ true };
    for (const char* word : { "온도", "습도", "기압" }) {
        if (!first) { out << ", "; }
        out << '"' << word << '"';
        first = false;
    }
    std::println("결과: {}", out.str());

    // istringstream으로 차례로 읽는다. 위치를 기억하므로 이어 읽을 수 있다.
    std::istringstream in{ R"("큰 방" 30.5 true "부엌" 21 false)" };
    Reading a{ parseReading(in) };
    Reading b{ parseReading(in) };
    std::println("{} / {}", a, b);

    // C++23: 고정된 버퍼 위의 스트림
    char text[]{ "11 2.5 hello" };
    // 끝의 널 문자는 빼고 넘긴다. 넣으면 마지막 문자열에 널 문자까지 읽힌다.
    std::ispanstream sin{ std::span{ text, sizeof(text) - 1 } };
    int i{ 0 };
    double d{ 0 };
    std::string s;
    sin >> i >> d >> s;
    std::println("{} {} {}", i, d, s);

    char buffer[32]{};
    std::ospanstream sout{ std::span{ buffer } };
    sout << "값=" << 42 << ' ' << 0.5;
    std::println("버퍼: \"{}\"", buffer);
}
