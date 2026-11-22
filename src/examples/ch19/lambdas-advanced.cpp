#include <concepts>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

// 람다를 돌려주는 함수. 반환 타입 추론(auto) 또는 std::function
auto makeScaler(double factor)
{
    return [factor](double x) { return x * factor; };   // 값으로 캡처해야 안전
    // return [&factor](double x) { ... };              // 버그: 매달린 참조
}

std::function<int()> makeCounter()
{
    return [n = 0]() mutable { return ++n; };   // 캡처 표현식으로 상태를 만듦
}

// 아무 호출할 수 있는 것이나 받아 두 번 부르는 제네릭 코드
decltype(auto) callTwice(auto&& f, auto&&... args)
{
    std::invoke(f, args...);
    return std::invoke(std::forward<decltype(f)>(f),
                       std::forward<decltype(args)>(args)...);
}

int main()
{
    // 제네릭 람다: 매개변수 타입을 auto로
    auto areEqual{ [](const auto& a, const auto& b) { return a == b; } };
    std::println("{} {}", areEqual(3, 3), areEqual(std::string{ "a" }, "b"));

    // 캡처 표현식: 둘러싼 범위에 없는 변수를 만들거나, 옮겨 넣는다.
    auto label{ std::make_unique<std::string>("온도") };
    auto show{ [prefix = "측정: ", l = std::move(label)](int v) {
        std::println("{}{} {}", prefix, *l, v);
    } };
    show(23);
    std::println("label은 비었나? {}", label == nullptr);

    // 템플릿 람다(C++20): 원소 타입을 이름으로 얻고, 두 인수의 타입을 같게
    auto firstOrDefault{ []<typename T>(const std::vector<T>& v) {
        return v.empty() ? T{} : v.front();
    } };
    std::println("{} '{}'", firstOrDefault(std::vector{ 7, 8 }),
                 firstOrDefault(std::vector<std::string>{}));
    auto sameTypeMax{ []<std::integral T>(T a, T b) { return a > b ? a : b; } };
    std::println("{}", sameTypeMax(3, 9));      // sameTypeMax(3, 9L)은 오류

    // 람다를 돌려받기
    auto toFahrenheitScale{ makeScaler(1.8) };
    std::println("{:.1f}", toFahrenheitScale(25.0));
    auto counter{ makeCounter() };
    counter();
    std::println("counter {}", counter());

    // 평가되지 않는 문맥, 기본 생성(상태 없는 람다, C++20)
    using Adder = decltype([](int a, int b) { return a + b; });
    Adder add;
    std::println("add {}", add(2, 3));

    // 재귀 람다(C++23): 명시적 객체 매개변수 this auto&
    auto fib{ [](this auto& self, int n) -> int {
        return n < 2 ? n : self(n - 1) + self(n - 2);
    } };
    for (int i{ 0 }; i < 10; ++i) { std::print("{} ", fib(i)); }
    std::println("");

    // invoke: 함수, 람다, 멤버 함수를 같은 방식으로 부른다.
    std::string word{ "invoke" };
    std::println("{} {}", std::invoke(&std::string::size, word),
                 std::invoke([](int x) { return x * x; }, 7));
    auto asDouble{ std::invoke_r<double>([](int a, int b) { return a / b; },
                                         7, 2) };                // C++23
    std::println("{}", asDouble);
    int hits{ 0 };
    callTwice([&hits](int step) { hits += step; }, 5);
    std::println("hits {}", hits);
}
