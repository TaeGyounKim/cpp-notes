#include <concepts>
#include <cstddef>
#include <numbers>
#include <print>
#include <string>
#include <vector>

// 축약 함수 템플릿: auto 매개변수마다 서로 다른 템플릿 타입 매개변수
decltype(auto) add(const auto& a, const auto& b) { return a + b; }

// 변수 템플릿
template <typename T>
constexpr T tau{ T{ 6.283185307179586476925286766559 } };

// 콘셉트: 상수 식 제약
template <typename T>
concept Big = sizeof(T) > 4;

// requires 식: 단순 요구 사항
template <typename T>
concept Incrementable = requires(T x) { x++; ++x; };

// 타입 요구 사항
template <typename T>
concept HasValueType = requires { typename T::value_type; };

// 복합 요구 사항: 식의 결과가 타입 제약을 만족하는가
template <typename T>
concept Sized = requires(const T x) {
    { x.size() } -> std::convertible_to<std::size_t>;
};

// 중첩 요구 사항
template <typename T>
concept SmallCounter = requires(T t) {
    ++t; --t;
    requires sizeof(t) <= 2;
};

// 결합
template <typename T>
concept SizedContainer = Sized<T> && HasValueType<T>;

static_assert(!Big<char>);
static_assert(Big<double>);

int main()
{
    std::println("{} {}", add(1, 2.5), add(std::string{ "센서" }, "-7"));
    std::println("{} {}", tau<float>, tau<double>);
    std::println("{}", std::numbers::pi);

    std::println("Incrementable: int {}, string {}",
                 Incrementable<int>, Incrementable<std::string>);
    std::println("HasValueType: vector {}, int {}",
                 HasValueType<std::vector<int>>, HasValueType<int>);
    std::println("Sized: string {}, double {}",
                 Sized<std::string>, Sized<double>);
    std::println("SmallCounter: short {}, int {}",
                 SmallCounter<short>, SmallCounter<int>);
    std::println("SizedContainer: vector {}", SizedContainer<std::vector<int>>);
}
