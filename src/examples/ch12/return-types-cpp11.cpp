#include <iostream>
#include <type_traits>
#include <utility>

// C++11: 반환 타입 추론(auto만)이 없다. 뒤에 오는 반환 타입을 쓴다.
template <typename T1, typename T2>
auto add(const T1& a, const T2& b) -> decltype(a + b)
{
    return a + b;
}

// 또는 std::declval로 매개변수 이름 없이 식의 타입을 구한다.
template <typename T1, typename T2>
decltype(std::declval<T1>() + std::declval<T2>()) add2(const T1& a,
                                                      const T2& b)
{
    return a + b;
}

int main()
{
    auto d = add(1, 2.5);
    auto e = add2(1, 2.5);
    std::cout << d << ' ' << e << ' '
              << std::is_same<decltype(d), double>::value << '\n';
}
