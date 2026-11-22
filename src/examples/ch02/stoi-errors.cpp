#include <print>
#include <stdexcept>
#include <string>

void tryParse(const std::string& text)
{
    try {
        int value{ std::stoi(text) };
        std::println("\"{}\" -> {}", text, value);
    } catch (const std::invalid_argument&) {
        std::println("\"{}\" -> 숫자로 읽을 수 없음", text);
    } catch (const std::out_of_range&) {
        std::println("\"{}\" -> int에 담기에는 너무 큼", text);
    }
}

int main()
{
    tryParse("2024");
    tryParse("abc");
    tryParse("99999999999999999999");
    tryParse("12abc");   // 읽을 수 있는 데까지만 읽는다. 예외가 아니다.
}
