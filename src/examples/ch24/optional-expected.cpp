#include <charconv>
#include <expected>
#include <optional>
#include <print>
#include <string>
#include <string_view>

// optional: 실패 이유 없이 "값이 없음"만 알린다.
std::optional<int> toInt(std::string_view text)
{
    int value{};
    auto [end, ec] { std::from_chars(text.data(), text.data() + text.size(),
                                     value) };
    if (ec != std::errc{} || end != text.data() + text.size()) { return {}; }
    return value;
}

// expected: 값 또는 "왜 실패했는지"
enum class AgeError { NotNumber, Negative, TooLarge };

std::string_view describe(AgeError e)
{
    switch (e) {
    case AgeError::NotNumber: return "숫자가 아님";
    case AgeError::Negative: return "음수";
    case AgeError::TooLarge: return "너무 큼";
    }
    return "?";
}

std::expected<int, AgeError> parseAge(std::string_view text)
{
    auto n{ toInt(text) };
    if (!n) { return std::unexpected{ AgeError::NotNumber }; }
    if (*n < 0) { return std::unexpected{ AgeError::Negative }; }
    if (*n > 150) { return std::unexpected{ AgeError::TooLarge }; }
    return *n;
}

int main()
{
    // optional의 모나드 연산: 값이 있는지 매번 검사하지 않고 잇는다.
    for (std::string_view in : { "21", "abc" }) {
        std::string out{ toInt(in)
            .and_then([](int v) -> std::optional<int> {
                if (v == 0) { return {}; }
                return 100 / v; })
            .transform([](int v) { return "결과 " + std::to_string(v); })
            .or_else([] { return std::optional<std::string>{ "값 없음" }; })
            .value() };
        std::println("{:>4} -> {}", in, out);
    }

    // expected: 성공이면 값, 실패면 이유
    for (std::string_view in : { "34", "-3", "999", "x" }) {
        auto age{ parseAge(in) };
        if (age) {
            std::println("{:>4} -> 나이 {}", in, *age);
        } else {
            std::println("{:>4} -> 오류: {}", in, describe(age.error()));
        }
    }

    // expected의 모나드 연산과 value_or
    auto nextYear{ parseAge("40").transform([](int a) { return a + 1; }) };
    std::println("내년 {}", nextYear.value_or(-1));
    auto msg{ parseAge("x").transform_error(
        [](AgeError e) { return std::string{ describe(e) }; }) };
    std::println("오류 문자열: {}", msg.error());
    std::println("기본 생성: optional 값 있음? {} / expected 값 있음? {}",
                 std::optional<int>{}.has_value(),
                 std::expected<int, AgeError>{}.has_value());
}
