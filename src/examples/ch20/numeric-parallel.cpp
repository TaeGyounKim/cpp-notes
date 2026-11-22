#include <algorithm>
#include <execution>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    // 병렬 실행 정책: 첫 인수로 넘긴다(구현이 실제로 병렬화할지는 구현 몫).
    std::vector<int> big(1'000'000);
    std::iota(big.begin(), big.end(), 1);           // 1, 2, 3, ...
    std::sort(std::execution::par, big.begin(), big.end(), std::greater<>{});
    std::println("병렬 정렬 뒤 첫 원소 {}", big.front());

    // 줄이기(reduce): accumulate와 같은 합이지만 병렬로 할 수 있다.
    std::vector values{ 1, 3, 6, 4, 6, 9 };
    long long sumSeq{ std::accumulate(values.cbegin(), values.cend(), 0LL) };
    long long sumPar{ std::reduce(std::execution::par_unseq, values.cbegin(),
                                  values.cend(), 0LL) };
    std::println("accumulate {} reduce {}", sumSeq, sumPar);

    // 내적: inner_product(순차), transform_reduce(병렬 가능)
    std::vector a{ 1, 2, 3, 4 };
    std::vector b{ 9, 8, 7, 6 };
    std::println("inner_product {} transform_reduce {}",
                 std::inner_product(a.cbegin(), a.cend(), b.cbegin(), 0),
                 std::transform_reduce(a.cbegin(), a.cend(), b.cbegin(), 0));
    // 단항 변환 뒤 합: 제곱합
    std::println("제곱합 {}", std::transform_reduce(a.cbegin(), a.cend(), 0,
                     std::plus<>{}, [](int x) { return x * x; }));

    // 훑기(scan): 누적 합
    std::vector<int> incl(a.size());
    std::vector<int> excl(a.size());
    std::inclusive_scan(a.cbegin(), a.cend(), incl.begin());
    std::exclusive_scan(a.cbegin(), a.cend(), excl.begin(), 0);
    std::println("inclusive {} exclusive {}", incl, excl);

    // 제약된 알고리즘: 범위를 통째로, 프로젝션, 뷰와 함께
    auto next{ [n = 0]() mutable { return ++n; } };
    std::vector<int> seq(5);
    std::ranges::generate(seq, std::ref(next));    // ref: 복사하지 않음
    std::println("generate {} / 다음 {}", seq, next());
    std::ranges::for_each(seq | std::views::filter([](int x) { return x % 2; }),
                          [](int& x) { x *= 10; });
    std::println("홀수만 10배 {}", seq);

    // C++23 제약된 판에만 있는 알고리즘
    std::vector<double> d{ 500.0, 10.0, 2.0 };
    std::println("contains {} starts_with {}", std::ranges::contains(seq, 30),
                 std::ranges::starts_with(seq, std::vector{ 10, 2 }));
    std::println("왼쪽 접기 {} 오른쪽 접기 {}",
                 std::ranges::fold_left_first(d, std::divides<>{}).value_or(0),
                 std::ranges::fold_right_last(d, std::divides<>{}).value_or(0));
}
