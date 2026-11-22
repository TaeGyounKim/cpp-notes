#include <print>

#if __has_include(<optional>)        // 헤더가 있는지 묻는다.
#include <optional>
#define HAVE_OPTIONAL 1
#endif

int main()
{
    // 언어 기능 검사 매크로: 값은 기능이 들어오거나 바뀐 연월(YYYYMM)
#ifdef __cpp_binary_literals
    std::println("2진 리터럴 지원: {}", __cpp_binary_literals);
#endif
#ifdef __cpp_consteval
    std::println("consteval 지원: {}", __cpp_consteval);
#endif
#if __has_cpp_attribute(nodiscard)
    std::println("[[nodiscard]] 지원: {}", __has_cpp_attribute(nodiscard));
#endif

#ifdef HAVE_OPTIONAL
    std::optional<int> value{ 42 };
    std::println("<optional>이 있다: {}", value.value());
#else
    std::println("<optional>이 없다");
#endif
}
