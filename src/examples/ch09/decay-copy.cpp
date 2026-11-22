#include <print>
#include <string>
#include <utility>

void consume(std::string&& text)   // 받은 문자열을 옮겨 가져간다.
{
    std::string mine{ std::move(text) };
    std::println("  가져감: \"{}\"", mine);
}

int main()
{
    std::string label{ "부엌" };

    // consume(label);             // 컴파일 오류: 좌측값
    consume(auto{ label });        // C++23: 사본을 우측값으로 만들어 넘김
    std::println("auto{{}} 뒤 label: \"{}\"", label);   // 그대로

    consume(std::move(label));     // 원본 자체를 넘김
    // 옮겨 간 뒤의 label은 쓰지 않는 것이 원칙(값이 정해져 있지 않음)
}
