#include <charconv>
#include <print>
#include <string>
#include <string_view>
#include <system_error>   // std::errc

int main()
{
    // 결과를 담을 공간은 부르는 쪽이 준비한다.
    std::string buffer(20, ' ');   // 공백 20개로 채운 문자열

    // 숫자 -> 문자: to_chars(시작, 끝, 값)
    auto [end, error]{ std::to_chars(buffer.data(),
                                     buffer.data() + buffer.size(), 12345) };
    if (error == std::errc{}) {   // std::errc{} 는 "오류 없음"
        std::println("[{}]", buffer);
        std::println("쓴 글자 수: {}", end - buffer.data());
    }

    // 문자 -> 숫자: from_chars(시작, 끝, 결과를 담을 변수)
    std::string_view text{ "678 apples" };
    int parsed{};
    auto [stop, error2]{ std::from_chars(text.data(),
                                         text.data() + text.size(), parsed) };
    if (error2 == std::errc{}) {
        std::println("{} / 남은 부분: \"{}\"", parsed, stop);
    }

    // 공간이 모자라면 오류를 알려 준다. 넘쳐 쓰지 않는다.
    std::string tiny(3, ' ');
    auto result{ std::to_chars(tiny.data(), tiny.data() + tiny.size(),
                               12345) };
    std::println("{}", result.ec == std::errc::value_too_large);
}
