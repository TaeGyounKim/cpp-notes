#include <any>
#include <format>
#include <print>
#include <string>
#include <variant>
#include <vector>

// 설정 값 하나는 정수, 실수, 문자열 중 하나다.
using Setting = std::variant<int, double, std::string>;

// 타입마다 다르게 처리하는 방문자(visitor)
struct Describe {
    std::string operator()(int i) const
    {
        return "정수 " + std::to_string(i);
    }
    std::string operator()(double d) const
    {
        return std::format("실수 {:.2f}", d);
    }
    std::string operator()(const std::string& s) const
    {
        return "문자열 " + s;
    }
};

// 람다 여러 개를 하나의 방문자로 묶는 흔한 도우미
template <typename... Fs>
struct Overloaded : Fs... { using Fs::operator()...; };

int main()
{
    Setting s;                                   // 첫 타입(int)의 기본값 0
    std::println("index {}, int? {}", s.index(),
                 std::holds_alternative<int>(s));
    s = 2.5;
    s = std::string{ "dark" };                   // 이제 문자열 하나만 담는다.
    std::println("index {}, {}", s.index(), std::get<std::string>(s));

    try {
        std::println("{}", std::get<int>(s));    // 지금은 int가 아니다.
    } catch (const std::bad_variant_access& e) {
        std::println("예외: {}", e.what());
    }
    if (int* p{ std::get_if<int>(&s) }) { std::println("int {}", *p); }
    else { std::println("int 아님(nullptr)"); }

    // visit: 담긴 타입에 맞는 호출 연산자가 불린다.
    std::vector<Setting> all{ 3, 0.75, std::string{ "ko" } };
    for (const auto& v : all) {
        std::println("{}", std::visit(Describe{}, v));
    }
    for (const auto& v : all) {
        std::visit(Overloaded{
            [](int i) { std::println("  i={}", i); },
            [](double d) { std::println("  d={}", d); },
            [](const std::string& t) { std::println("  s={}", t); } }, v);
    }

    // any: 아무 타입이나 하나. 꺼낼 때 any_cast
    std::any box;
    std::println("비었나? {}", !box.has_value());
    box = 42;
    std::println("{} / 타입 int? {}", std::any_cast<int>(box),
                 box.type() == typeid(int));
    box = std::string{ "hello" };                // 다른 타입으로 바꿔도 됨
    try {
        std::println("{}", std::any_cast<int>(box));
    } catch (const std::bad_any_cast& e) {
        std::println("예외: {}", e.what());
    }
    // 포인터를 넘기는 any_cast는 실패하면 nullptr를 돌려준다.
    if (auto* str{ std::any_cast<std::string>(&box) }) {
        std::println("문자열 {}", *str);
    }
}
