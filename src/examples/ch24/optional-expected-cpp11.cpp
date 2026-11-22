#include <cstdlib>
#include <iostream>
#include <string>

// optional은 C++17, expected는 C++23부터다. 그 이전에는 성공 여부와 값,
// 오류를 함께 담는 구조체를 만들거나, bool을 돌려주고 출력 매개변수를 쓴다.
enum class AgeError { None, NotNumber, Negative, TooLarge };

struct AgeResult {
    int value;
    AgeError error;
    bool ok() const { return error == AgeError::None; }
};

AgeResult parseAge(const std::string& text)
{
    char* end = nullptr;
    long n = std::strtol(text.c_str(), &end, 10);
    if (text.empty() || *end != '\0') { return { 0, AgeError::NotNumber }; }
    if (n < 0) { return { 0, AgeError::Negative }; }
    if (n > 150) { return { 0, AgeError::TooLarge }; }
    return { static_cast<int>(n), AgeError::None };
}

int main()
{
    const char* inputs[] = { "34", "-3", "x" };
    for (const char* in : inputs) {
        AgeResult r = parseAge(in);
        if (r.ok()) {
            std::cout << in << " -> " << r.value << '\n';
        } else {
            std::cout << in << " -> error " << static_cast<int>(r.error)
                      << '\n';
        }
    }
}
