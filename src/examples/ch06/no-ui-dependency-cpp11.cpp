#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

// std::expected(C++23)가 없으면 예외로 오류를 알린다.
// 라이브러리는 출력하지 않고, 부르는 쪽이 catch해서 알린다.
int parsePercent(const std::string& text)
{
    std::size_t used{ 0 };
    int value{ 0 };
    try {
        value = std::stoi(text, &used);
    } catch (const std::exception&) {
        throw std::invalid_argument{ "숫자가 아님: " + text };
    }
    if (used != text.size()) {
        throw std::invalid_argument{ "숫자가 아님: " + text };
    }
    if (value < 0 || value > 100) {
        throw std::out_of_range{ "범위(0~100) 밖: " + text };
    }
    return value;
}

int main()
{
    const std::string inputs[]{ "75", "abc", "120" };
    for (const auto& input : inputs) {
        try {
            const int value{ parsePercent(input) };
            std::cout << "값: " << value << '\n';
        } catch (const std::exception& error) {
            std::cout << "[경고] " << error.what() << '\n';
        }
    }
}
