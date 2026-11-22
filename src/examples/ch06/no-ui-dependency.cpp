#include <charconv>
#include <expected>
#include <print>
#include <string>
#include <string_view>

// 나쁜 라이브러리 함수: 오류를 직접 화면에 찍고 아무 값이나 돌려준다.
// 그래픽 앱에는 콘솔이 없고, 부르는 쪽은 실패했는지 알 수 없다.
int parsePercentBad(std::string_view text)
{
    int value{ 0 };
    auto [end, error]{ std::from_chars(text.data(),
                                       text.data() + text.size(), value) };
    if (error != std::errc{} || value < 0 || value > 100) {
        std::println("잘못된 값입니다!");
        return 0;
    }
    return value;
}

// 좋은 라이브러리 함수: 결과나 오류를 돌려주기만 한다.
// 사용자에게 어떻게 알릴지는 부르는 쪽이 정한다.
std::expected<int, std::string> parsePercent(std::string_view text)
{
    int value{ 0 };
    auto [end, error]{ std::from_chars(text.data(),
                                       text.data() + text.size(), value) };
    if (error != std::errc{} || end != text.data() + text.size()) {
        return std::unexpected{ "숫자가 아님: " + std::string{ text } };
    }
    if (value < 0 || value > 100) {
        return std::unexpected{ "범위(0~100) 밖: " + std::string{ text } };
    }
    return value;
}

int main()
{
    std::println("나쁜 함수: {}", parsePercentBad("abc"));

    for (std::string_view input : { "75", "abc", "120" }) {
        if (auto result{ parsePercent(input) }; result) {
            std::println("값: {}", *result);
        } else {
            // 부르는 쪽이 고른 방식으로 알린다. 조용히 넘어갈 수도 있다.
            std::println("[경고] {}", result.error());
        }
    }
}
