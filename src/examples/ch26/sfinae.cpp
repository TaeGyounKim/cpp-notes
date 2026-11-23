#include <concepts>
#include <print>
#include <string>
#include <type_traits>

// 1) 반환 타입에 enable_if: 조건이 거짓인 오버로드는 후보에서 빠진다(SFINAE).
template <typename A, typename B>
std::enable_if_t<std::is_same_v<A, B>, bool> check(const A&, const B&)
{
    std::println("  같은 타입");
    return true;
}
template <typename A, typename B>
std::enable_if_t<!std::is_same_v<A, B>, bool> check(const A&, const B&)
{
    std::println("  다른 타입");
    return false;
}

// 2) 이름 없는 템플릿 매개변수에 enable_if: 반환 타입이 깔끔하다.
//    생성자처럼 반환 타입이 없는 곳에서는 이 방법을 쓴다.
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
void half(T v) { std::println("  정수 나누기 {}", v / 2); }
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void half(T v) { std::println("  실수 나누기 {}", v / 2); }

// 3) 같은 일을 C++20 콘셉트로: 훨씬 읽기 쉽다.
void half2(std::integral auto v) { std::println("  정수 {}", v / 2); }
void half2(std::floating_point auto v) { std::println("  실수 {}", v / 2); }

// 4) if constexpr: 고르지 않은 쪽은 컴파일되지 않는다.
struct Robot {
    void work() const { std::println("  Robot::work()"); }
};
template <typename T>
void try_work(const T& t)
{
    if constexpr (requires { t.work(); }) {   // requires 식으로 바로 검사
        t.work();
    } else {
        std::println("  work()가 없음");
    }
}

// 5) static_assert: 조건이 거짓이면 그 메시지로 컴파일 오류
template <typename T>
T twice(T v)
{
    static_assert(std::is_arithmetic_v<T>, "twice()는 산술 타입만 받는다");
    return v * 2;
}

int main()
{
    std::println("check:");
    check(1, 32);
    check(1, 3.5);
    check(3.5, std::string{ "x" });

    std::println("half:");
    half(7);
    half(7.0);
    // half(std::string{});   // 오류: 알맞은 오버로드가 없음
    half2(9);
    half2(9.0f);

    std::println("try_work:");
    try_work(Robot{});
    try_work(123);

    // 논리 트레이트: 트레이트 여럿을 AND, OR, NOT으로 묶는다.
    std::println("{} {} {}",
                 std::conjunction_v<std::is_integral<int>,
                                    std::is_integral<short>>,
                 std::disjunction_v<std::is_integral<double>,
                                    std::is_integral<long>>,
                 std::negation_v<std::is_integral<int>>);

    static_assert(sizeof(void*) == 8, "64비트로 컴파일해야 한다");
    std::println("{}", twice(21));
    // twice(std::string{});   // 오류: "twice()는 산술 타입만 받는다"
}
