#include <cstddef>
#include <print>
#include <string>
#include <tuple>
#include <utility>

// 1) 컴파일 시간 계산: 템플릿 재귀로 2의 거듭제곱
template <unsigned N>
struct Pow2 {
    static constexpr unsigned long long value{ 2 * Pow2<N - 1>::value };
};
template <>
struct Pow2<0> {                       // 기저(완전 특수화)
    static constexpr unsigned long long value{ 1 };
};

// 같은 일을 consteval 함수로: 반드시 컴파일 시간에 실행된다.
consteval unsigned long long pow2(unsigned n)
{
    return n == 0 ? 1 : 2 * pow2(n - 1);
}

// 2) 반복문 펼치기: Repeat<3>::run(f)는 f(1); f(2); f(3);이 된다.
template <int I>
struct Repeat {
    template <typename F>
    static void run(F f)
    {
        Repeat<I - 1>::run(f);
        f(I);
    }
};
template <>
struct Repeat<0> {
    template <typename F>
    static void run(F) {}
};

// 3) tuple 원소를 차례로: if constexpr로 재귀를 멈춘다.
template <typename Tuple, std::size_t N = std::tuple_size_v<Tuple>>
void show_each(const Tuple& t)
{
    if constexpr (N > 1) { show_each<Tuple, N - 1>(t); }
    std::println("  [{}] {}", N - 1, std::get<N - 1>(t));
}

// 4) 인덱스 시퀀스 + 폴드: 0, 1, ..., n-1을 한꺼번에 펼친다.
template <typename Tuple, std::size_t... I>
void show_all(const Tuple& t, std::index_sequence<I...>)
{
    ((std::print("{}{}", I == 0 ? "" : " | ", std::get<I>(t))), ...);
    std::println("");
}
template <typename... Ts>
void show_all(const std::tuple<Ts...>& t)
{
    show_all(t, std::index_sequence_for<Ts...>{});
}

int main()
{
    // 값은 컴파일 시간에 정해진 상수: static_assert로 확인할 수 있다.
    static_assert(Pow2<10>::value == 1024);
    static_assert(pow2(20) == 1'048'576);
    std::println("{} {}", Pow2<16>::value, pow2(40));

    Repeat<3>::run([](int i) { std::print("step{} ", i); });
    std::println("");

    std::tuple record{ 42, std::string{ "kim" }, 3.5, true };
    show_each(record);
    show_all(record);
}
