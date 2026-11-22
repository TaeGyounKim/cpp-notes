#include <charconv>
#include <print>
#include <string>
#include <system_error>

int main()
{
    double original{ 0.1 + 0.2 };

    // 방법 1: to_chars / from_chars
    std::string buffer(40, ' ');
    auto [end, error]{ std::to_chars(buffer.data(),
                                     buffer.data() + buffer.size(),
                                     original) };
    double restored{};
    std::from_chars(buffer.data(), end, restored);
    std::println("to_chars : {}", std::string{ buffer.data(), end });
    std::println("  되돌린 값이 원래 값과 같은가: {}", original == restored);

    // 방법 2: to_string / stod
    std::string text{ std::to_string(original) };
    double restored2{ std::stod(text) };
    std::println("to_string: {}", text);
    std::println("  되돌린 값이 원래 값과 같은가: {}", original == restored2);

    if (error != std::errc{}) {
        std::println("변환 실패");
    }
}
