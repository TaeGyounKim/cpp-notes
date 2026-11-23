#include <iostream>
#include <type_traits>

// enable_if, static_assert는 C++11부터 있다. _t/_v 별칭(C++14/17),
// if constexpr(C++17), 콘셉트·requires(C++20)가 없으므로
// "식 SFINAE": decltype 안의 식이 안 되면 그 오버로드가 빠진다.
template <typename T,
          typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
void half(T v) { std::cout << "int " << v / 2 << '\n'; }
template <typename T,
          typename std::enable_if<std::is_floating_point<T>::value,
                                  int>::type = 0>
void half(T v) { std::cout << "float " << v / 2 << '\n'; }

struct Robot {
    void work() const { std::cout << "Robot::work()\n"; }
};
// t.work()가 되는 타입에만: 0은 int라 이쪽이 더 잘 맞는다.
template <typename T>
auto try_work_impl(const T& t, int) -> decltype(t.work(), void())
{
    t.work();
}
template <typename T>
void try_work_impl(const T&, long) { std::cout << "no work()\n"; }
template <typename T>
void try_work(const T& t) { try_work_impl(t, 0); }

int main()
{
    static_assert(sizeof(void*) == 8, "64-bit only");
    half(7);
    half(7.0);
    try_work(Robot());
    try_work(123);
}
