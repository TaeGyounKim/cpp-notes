#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

// 가변 인자 템플릿과 sizeof...은 C++11부터 있다.
// if constexpr와 폴드 표현식(C++17)이 없으므로 재귀와 기저 함수로 처리한다.
void describe(int v) { std::cout << "int " << v << '\n'; }
void describe(double v) { std::cout << "double " << v << '\n'; }
void describe(const std::string& v) { std::cout << "string " << v << '\n'; }

void walk() {}
template <typename First, typename... Rest>
void walk(First&& first, Rest&&... rest)
{
    describe(std::forward<First>(first));
    walk(std::forward<Rest>(rest)...);
}

// 합계도 재귀로: 인수 하나가 기저
template <typename T>
T total(const T& v) { return v; }
template <typename T, typename... Ts>
T total(const T& first, const Ts&... rest) { return first + total(rest...); }

template <typename... Ts>
std::size_t count(const Ts&...) { return sizeof...(Ts); }   // 인수 개수

int main()
{
    walk(1, 2.5, std::string("hi"));
    std::cout << total(1, 2, 3) << ' ' << count(1, 'a', 2.0) << '\n';
}
