#include <iostream>
#include <string>
#include <type_traits>

// 축약 함수 템플릿(C++20) 대신 보통의 함수 템플릿과 뒤에 오는 반환 타입
template <typename T1, typename T2>
auto add(const T1& a, const T2& b) -> decltype(a + b) { return a + b; }

// 변수 템플릿(C++14) 대신 constexpr 함수 템플릿
template <typename T>
constexpr T tau() { return T(6.283185307179586476925286766559L); }

// 콘셉트(C++20) 대신 타입 특성과 static_assert
template <typename T>
struct IsBig : std::integral_constant<bool, (sizeof(T) > 4)> {};

static_assert(!IsBig<char>::value, "char는 크지 않다");
static_assert(IsBig<double>::value, "double은 크다");

int main()
{
    std::cout << add(1, 2.5) << ' ' << add(std::string("센서"), "-7") << ' '
              << tau<float>() << '\n';
}
