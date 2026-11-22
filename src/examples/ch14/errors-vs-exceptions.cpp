#include <print>
#include <stdexcept>
#include <string>

// 방법 1: 반환 코드. 결과는 출력 매개변수로, 성공 여부는 반환값으로
bool parseCelsiusCode(const std::string& text, double& out)
{
    if (text.empty()) { return false; }
    out = std::stod(text);
    return true;
}

// 중간 함수도 오류를 확인해 위로 넘겨야 한다.
bool averageCode(const std::string& a, const std::string& b, double& out)
{
    double x{ 0 }, y{ 0 };
    if (!parseCelsiusCode(a, x)) { return false; }
    if (!parseCelsiusCode(b, y)) { return false; }
    out = (x + y) / 2;
    return true;
}

// 방법 2: 예외. 결과는 반환값으로, 오류는 예외로
double parseCelsius(const std::string& text)
{
    if (text.empty()) { throw std::invalid_argument{ "빈 문자열" }; }
    return std::stod(text);
}

// 중간 함수에 오류 처리 코드가 없다. 예외는 그대로 위로 지나간다.
double average(const std::string& a, const std::string& b)
{
    return (parseCelsius(a) + parseCelsius(b)) / 2;
}

int main()
{
    double result{ 0 };
    if (averageCode("21.5", "", result)) {
        std::println("평균 {}", result);
    } else {
        std::println("반환 코드: 실패(이유는 모름)");
    }

    try {
        std::println("평균 {}", average("21.5", "23.5"));
        std::println("평균 {}", average("21.5", ""));
        std::println("여기는 실행되지 않는다");
    } catch (const std::invalid_argument& e) {
        std::println("예외: {}", e.what());   // 이유가 함께 온다.
    }
}
