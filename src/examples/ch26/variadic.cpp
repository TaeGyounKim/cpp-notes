#include <concepts>
#include <print>
#include <string>
#include <utility>

// 타입마다 처리 방법을 오버로드로 준다.
void describe(int v) { std::println("  정수 {}", v); }
void describe(double v) { std::println("  실수 {}", v); }
void describe(const std::string& v) { std::println("  문자열 \"{}\"", v); }

// 1) 재귀: 첫 인수를 처리하고 나머지로 다시 부른다. 기저가 필요하다.
void walk() {}
template <typename First, typename... Rest>
void walk(First&& first, Rest&&... rest)
{
    describe(std::forward<First>(first));
    walk(std::forward<Rest>(rest)...);         // 팩 확장
}

// 2) if constexpr: 남은 인수가 없으면 재귀 호출 자체를 컴파일하지 않는다.
template <typename First, typename... Rest>
void walk2(First&& first, Rest&&... rest)
{
    describe(std::forward<First>(first));
    if constexpr (sizeof...(rest) > 0) { walk2(std::forward<Rest>(rest)...); }
}

// 3) 폴드 표현식: 쉼표 연산자로 펼치면 재귀도 기저도 없다.
template <typename... Ts>
void walk3(Ts&&... args) { (describe(std::forward<Ts>(args)), ...); }

// 이항 왼쪽 폴드: (((init + a) + b) + c)
template <typename T, typename... Ts>
auto total(const T& init, const Ts&... rest) { return (init + ... + rest); }

// 가변 인자 콘셉트: 모두 같은 타입이어야 한다.
template <typename T, typename... Us>
concept AllSame = (std::same_as<T, Us> && ...);

template <typename T, typename... Ts>
    requires AllSame<T, Ts...>
auto strict_total(const T& init, const Ts&... rest)
{
    return (init + ... + rest);
}

// 빈 팩: &&는 true, ||는 false
template <typename... Ts>
bool all_positive(const Ts&... v) { return ((v > 0) && ...); }
template <typename... Ts>
bool any_positive(const Ts&... v) { return ((v > 0) || ...); }

// 믹스인 여러 개를 상속하는 클래스
struct Named {
    std::string name;
    void hello() const { std::println("  이름 {}", name); }
};
struct Counted {
    int count;
    void show() const { std::println("  개수 {}", count); }
};
template <typename... Mixins>
class Thing : public Mixins... {
public:
    explicit Thing(const Mixins&... m) : Mixins{ m }... {}
};

int main()
{
    std::println("walk:");
    walk(1, 2.5, std::string{ "hi" });
    std::println("walk2:");
    walk2(std::string{ "a" }, 3);
    std::println("walk3:");
    walk3(4.0, 5, std::string{ "z" });

    std::println("total {} / {} / {}", total(1, 2, 3.5), total(10),
                 total(std::string{ "ab" }, "cd", "ef"));
    std::println("strict {}", strict_total(1.5, 2.5));
    // strict_total(1, 2.5);   // 오류: int와 double이 섞임

    std::println("{} {} {}", all_positive(1, 2), all_positive(1, -2),
                 all_positive());
    std::println("{} {}", any_positive(-1, 3), any_positive());

    Thing<Named, Counted> t{ Named{ "box" }, Counted{ 3 } };
    t.hello();
    t.show();
    Thing<Named> u{ Named{ "only" } };
    u.hello();
    // u.show();   // 오류: Counted를 상속하지 않음
}
