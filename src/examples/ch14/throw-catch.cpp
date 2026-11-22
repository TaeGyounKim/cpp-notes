#include <fstream>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// 파일에서 정수를 읽는다. 열 수 없으면 invalid_argument,
// 중간에 숫자가 아닌 것이 있으면 runtime_error를 던진다.
std::vector<int> readNumbers(const std::string& file)
{
    std::ifstream in{ file };
    if (in.fail()) {
        throw std::invalid_argument{ "파일을 열 수 없음: " + file };
    }
    std::vector<int> numbers;
    int value{ 0 };
    while (in >> value) { numbers.push_back(value); }
    if (!in.eof()) {                 // 파일 끝 전에 멈췄다면 읽기 오류
        throw std::runtime_error{ "읽기 오류: " + file };
    }
    return numbers;
}

int load(const std::string& file)
{
    try {
        std::vector<int> numbers{ readNumbers(file) };
        std::println("{}: {}", file, numbers);
        return 0;
    } catch (const std::invalid_argument& e) {   // 먼저 맞는 것이 잡는다.
        std::println("열기 실패 -> {}", e.what());
        return 1;
    } catch (const std::runtime_error& e) {
        std::println("형식 오류 -> {}", e.what());
        return 2;
    }
}

int main()
{
    std::ofstream{ "good.txt" } << "3 1 4 1 5";
    std::ofstream{ "bad.txt" } << "3 1 x 5";

    std::println("결과 {}", load("good.txt"));
    std::println("결과 {}", load("bad.txt"));
    std::println("결과 {}", load("missing.txt"));

    // 객체가 아닌 것도 던질 수 있지만 권하지 않는다.
    try {
        throw 42;
    } catch (int code) {
        std::println("int를 잡음: {}", code);
    }

    // catch (...)는 무엇이든 잡는다. 대신 무엇인지 알 수 없다.
    try {
        throw "C 문자열";
    } catch (...) {
        std::println("알 수 없는 예외를 잡음");
    }
}
