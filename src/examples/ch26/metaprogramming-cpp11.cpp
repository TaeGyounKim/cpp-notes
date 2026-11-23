#include <cstddef>
#include <iostream>
#include <string>
#include <tuple>

// consteval(C++20), if constexpr(C++17), index_sequence(C++14)가 없으므로
// constexpr 함수(본문은 return 하나), 부분 특수화 재귀로 처리한다.
template <unsigned N>
struct Pow2 {
    static const unsigned long long value = 2 * Pow2<N - 1>::value;
};
template <>
struct Pow2<0> {
    static const unsigned long long value = 1;
};

constexpr unsigned long long pow2(unsigned n)   // C++11: 식 하나
{
    return n == 0 ? 1 : 2 * pow2(n - 1);
}

// tuple 원소: 기저를 부분 특수화로
template <typename Tuple, std::size_t N>
struct ShowEach {
    static void run(const Tuple& t)
    {
        ShowEach<Tuple, N - 1>::run(t);
        std::cout << std::get<N - 1>(t) << '\n';
    }
};
template <typename Tuple>
struct ShowEach<Tuple, 0> {
    static void run(const Tuple&) {}
};

int main()
{
    static_assert(Pow2<10>::value == 1024, "2^10");
    static_assert(pow2(20) == 1048576, "2^20");
    std::cout << Pow2<16>::value << ' ' << pow2(40) << '\n';

    std::tuple<int, std::string, double> record(42, "kim", 3.5);
    ShowEach<decltype(record), 3>::run(record);
}
