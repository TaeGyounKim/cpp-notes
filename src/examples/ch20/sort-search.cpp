#include <algorithm>
#include <functional>
#include <iterator>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector scores{ 72, 95, 58, 88, 64, 91, 77 };

    // 분할: 조건이 참인 원소를 앞으로(순서는 보장 안 됨)
    std::vector<int> pass(scores.size());
    std::vector<int> fail(scores.size());
    auto [passEnd, failEnd]{ std::partition_copy(
        scores.cbegin(), scores.cend(), pass.begin(), fail.begin(),
        [](int s) { return s >= 70; }) };
    pass.erase(passEnd, pass.end());
    fail.erase(failEnd, fail.end());
    std::println("합격 {} 불합격 {}", pass, fail);

    auto parted{ scores };
    auto point{ std::partition(parted.begin(), parted.end(),
                               [](int s) { return s >= 70; }) };
    std::println("partition {} / 경계 위치 {}", parted, point - parted.begin());

    // 정렬
    auto sorted{ scores };
    std::sort(sorted.begin(), sorted.end(), std::greater<>{});   // 내림차순
    std::println("sort 내림차순 {} / is_sorted(오름)? {}", sorted,
                 std::is_sorted(sorted.cbegin(), sorted.cend()));

    // nth_element: 세 번째로 큰 값만 제자리에(선형 시간)
    auto work{ scores };
    std::nth_element(work.begin(), work.begin() + 2, work.end(),
                     std::greater<>{});
    std::println("세 번째로 큰 점수 {}", work[2]);
    std::sort(work.begin(), work.begin() + 3, std::greater<>{});   // 상위 셋
    std::println("상위 셋 {}", std::vector(work.begin(), work.begin() + 3));

    // 이진 탐색: 정렬된 범위에서 로그 시간
    std::ranges::sort(sorted);                   // 다시 오름차순
    auto pos{ std::lower_bound(sorted.begin(), sorted.end(), 80) };
    sorted.insert(pos, 80);                       // 정렬을 유지하며 넣기
    std::println("80 넣은 뒤 {} / 91 있나? {}", sorted,
                 std::binary_search(sorted.cbegin(), sorted.cend(), 91));

    // 집합 알고리즘: 정렬된 범위
    std::vector monday{ 1, 3, 5, 7 };             // 출석한 학생 번호
    std::vector tuesday{ 3, 4, 5 };
    std::vector<int> result(monday.size() + tuesday.size());
    auto end{ std::set_intersection(monday.cbegin(), monday.cend(),
                                    tuesday.cbegin(), tuesday.cend(),
                                    result.begin()) };
    std::println("이틀 다 {}", std::ranges::subrange(result.begin(), end));
    end = std::set_symmetric_difference(monday.cbegin(), monday.cend(),
                                        tuesday.cbegin(), tuesday.cend(),
                                        result.begin());
    std::println("하루만 {}", std::ranges::subrange(result.begin(), end));
    std::vector<int> merged;
    std::merge(monday.cbegin(), monday.cend(), tuesday.cbegin(),
               tuesday.cend(), std::back_inserter(merged));
    std::println("merge {} / includes? {}", merged,
                 std::includes(monday.cbegin(), monday.cend(),
                               tuesday.cbegin(), tuesday.cend()));

    // 최소·최대
    auto [lo, hi]{ std::minmax_element(scores.cbegin(), scores.cend()) };
    std::println("최저 {} 최고 {}", *lo, *hi);
    std::println("max({{3, 9, 4}}) {} / clamp(105) {}", std::max({ 3, 9, 4 }),
                 std::clamp(105, 0, 100));
}
