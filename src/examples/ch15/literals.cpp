#include <chrono>
#include <complex>
#include <cstddef>
#include <print>
#include <string>
#include <string_view>
#include <type_traits>

// 길이를 늘 미터로 저장한다. 리터럴로만 만들게 생성자를 감춘다.
class Length
{
public:
    long double meters() const { return m_meters; }
    friend Length operator""_km(long double d);
    friend Length operator""_m(long double d);
    friend Length operator""_cm(const char* raw);

private:
    explicit Length(long double meters) : m_meters{ meters } {}
    long double m_meters;
};

// 조리된(cooked) 리터럴 연산자: 이미 해석된 수를 받는다.
Length operator""_km(long double d) { return Length{ d * 1000 }; }
Length operator""_m(long double d) { return Length{ d }; }

// 날(raw) 리터럴 연산자: 글자 그대로 받는다("125" -> '1' '2' '5').
Length operator""_cm(const char* raw)
{
    long double value{ 0 };
    for (const char* p{ raw }; *p != '\0'; ++p) {
        if (*p >= '0' && *p <= '9') { value = value * 10 + (*p - '0'); }
    }
    return Length{ value / 100 };
}

// 문자열 리터럴용: 포인터와 길이를 받는다.
std::string operator""_up(const char* text, std::size_t length)
{
    std::string result{ text, length };
    for (char& c : result) {
        if (c >= 'a' && c <= 'z') { c = static_cast<char>(c - 'a' + 'A'); }
    }
    return result;
}

int main()
{
    Length a{ 1.2_km };
    auto b{ 3.5_m };
    auto c{ 125_cm };
    std::println("{}m {}m {}m", a.meters(), b.meters(), c.meters());

    auto shout{ "hello"_up };
    std::println("{} (string? {})", shout,
                 std::is_same_v<decltype(shout), std::string>);

    // 표준 리터럴: 밑줄로 시작하지 않는다.
    using namespace std::literals;
    auto s{ "센서"s };             // std::string
    auto v{ "센서"sv };            // std::string_view
    auto t{ 90min + 30s };         // std::chrono::duration
    auto z{ 1.5i };                // std::complex<double>
    std::println("{} {} {}초 {}", s.size(), v.size(),
                 std::chrono::seconds{ t }.count(), z.imag());
}
