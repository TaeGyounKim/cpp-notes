#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// <type_traits>는 C++11부터 있다. _v 변수 템플릿(C++17)과 _t 별칭(C++14)이
// 없으므로 ::value와 typename ...::type을 쓴다.
template <typename T>
void describe_impl(const T& v, std::true_type)
{
    std::cout << v << ": integral\n";
}
template <typename T>
void describe_impl(const T& v, std::false_type)
{
    std::cout << v << ": not integral\n";
}
template <typename T>
void describe(const T& v) { describe_impl(v, std::is_integral<T>()); }

template <typename T>
typename std::conditional<std::is_nothrow_move_assignable<T>::value, T&&,
                          const T&>::type
move_assign_if_noexcept(T& t) noexcept
{
    return std::move(t);
}

int main()
{
    describe(42);
    describe(std::string("text"));
    std::cout << std::boolalpha
              << std::is_same<std::remove_pointer<int*>::type, int>::value
              << '\n';
    std::string a = "x", b = "y";
    a = move_assign_if_noexcept(b);   // string의 이동 대입은 noexcept
    std::cout << a << '\n';
}
