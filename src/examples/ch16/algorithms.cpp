#include <algorithm>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <vector>

int main()
{
    std::vector<int> v{ 5, 3, 8, 3, 1, 9, 2 };

    // 바꾸지 않는 알고리즘: 찾기, 세기, 비교
    auto it{ std::find(v.begin(), v.end(), 8) };
    std::println("8의 위치 {}, 3은 {}개, 모두 양수? {}", it - v.begin(),
                 std::count(v.begin(), v.end(), 3),
                 std::all_of(v.begin(), v.end(), [](int x) { return x > 0; }));

    // 바꾸는 알고리즘: 복사, 변환, 지우기
    std::vector<int> doubled(v.size());
    std::transform(v.begin(), v.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    std::println("두 배 {}", doubled);

    // 정렬과 이진 탐색(정렬된 범위에서)
    std::vector<int> sorted{ v };
    std::sort(sorted.begin(), sorted.end());
    std::println("정렬 {}, 5가 있나? {}", sorted,
                 std::binary_search(sorted.begin(), sorted.end(), 5));
    auto lo{ std::lower_bound(sorted.begin(), sorted.end(), 4) };
    std::println("4 이상인 첫 원소 {}", *lo);

    // 집합 연산(정렬된 범위)
    std::set<int> a{ 1, 2, 3, 4 };
    std::set<int> b{ 3, 4, 5 };
    std::vector<int> both;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(both));
    std::println("교집합 {}", both);

    // 최솟값·최댓값, 범위 제한
    auto [mn, mx]{ std::minmax_element(v.begin(), v.end()) };
    std::println("최소 {} 최대 {}, clamp(15, 0, 10) = {}", *mn, *mx,
                 std::clamp(15, 0, 10));

    // 수치 알고리즘(<numeric>)
    std::vector<int> seq(5);
    std::iota(seq.begin(), seq.end(), 1);              // 1 2 3 4 5
    std::println("{} 합 {}", seq, std::accumulate(seq.begin(), seq.end(), 0));

    // 범위(ranges) 판: 반복자 쌍 대신 컨테이너를 통째로
    std::ranges::sort(v);
    std::println("ranges::sort {}, contains 9? {}", v,
                 std::ranges::contains(v, 9));          // C++23
    int total{ std::ranges::fold_left(v, 0, std::plus{}) };   // C++23
    std::println("fold_left 합 {}", total);
}
