#include <print>
#include <string>

int main()
{
    // 숫자 -> 문자열
    std::string count{ std::to_string(42) };
    std::string ratio{ std::to_string(3.14) };
    std::println("[{}] [{}]", count, ratio);
    std::println("{}", count + "개");

    // 문자열 -> 숫자
    int number{ std::stoi("123") };
    double real{ std::stod("2.5") };
    std::println("{} {}", number + 1, real * 2);

    // 앞쪽 공백은 건너뛰고, 숫자로 읽을 수 없는 글자에서 멈춘다.
    // 둘째 인수에 변수의 주소를 넘기면 멈춘 위치를 알려 준다.
    const std::string price{ "  123USD" };
    std::size_t index{ 0 };
    int value{ std::stoi(price, &index) };
    std::println("값: {}, 멈춘 곳의 글자: '{}'", value, price[index]);

    // 셋째 인수는 진법. 0을 주면 접두어를 보고 스스로 판단한다.
    std::println("{}", std::stoi("ff", nullptr, 16));
    std::println("{}", std::stoi("0x1A", nullptr, 0));   // 16진수
    std::println("{}", std::stoi("017", nullptr, 0));    // 8진수
    std::println("{}", std::stoi("17", nullptr, 0));     // 10진수
}
