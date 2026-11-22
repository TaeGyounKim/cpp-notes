#include <algorithm>
#include <compare>
#include <functional>
#include <list>
#include <print>
#include <string>
#include <vector>

int main()
{
    std::vector levels{ 3, 4, 7, 6, 6, 2 };   // 시간대별 소음 등급
    auto first{ levels.cbegin() };
    auto last{ levels.cend() };

    // 찾기 알고리즘들
    auto it{ std::find_if_not(first, last, [](int x) { return x < 5; }) };
    std::println("처음으로 5 이상: {}", *it);
    it = std::adjacent_find(first, last);                 // 이웃한 같은 값
    std::println("연속으로 같은 값: {} (위치 {})", *it, it - first);
    std::vector targets{ 7, 2 };
    it = std::find_first_of(first, last, targets.cbegin(), targets.cend());
    std::println("7이나 2 중 먼저 나온 것: {}", *it);
    std::vector pattern{ 6, 2 };
    it = std::search(first, last, pattern.cbegin(), pattern.cend());
    std::println("부분 순서열 {{6, 2}} 위치 {}", it - first);
    it = std::search_n(first, last, 2, 6);                // 6이 연속 2번
    std::println("6이 두 번 연속 시작 위치 {}", it - first);

    // 보이어-무어 탐색기: 긴 글에서 낱말 찾기
    std::string text{ "the quick sensor reported a quiet room" };
    std::string word{ "quiet" };
    std::boyer_moore_searcher searcher{ word.cbegin(), word.cend() };
    auto found{ std::search(text.cbegin(), text.cend(), searcher) };
    std::println("'{}'는 {}번째 글자부터", word, found - text.cbegin());

    // 비교: 서로 다른 컨테이너끼리도 된다(반복자 넷 판을 쓴다)
    std::list<int> other{ 3, 4, 9 };
    bool same{ std::equal(first, last, other.cbegin(), other.cend()) };
    auto [mine, theirs]{ std::mismatch(first, last,
                                       other.cbegin(), other.cend()) };
    std::println("같은가? {} / 처음 다른 곳: {} vs {}", same, *mine, *theirs);
    std::println("vector가 사전식으로 먼저? {}",
                 std::lexicographical_compare(first, last,
                                              other.cbegin(), other.cend()));
    auto order{ std::lexicographical_compare_three_way(
        first, last, other.cbegin(), other.cend()) };     // C++20
    std::println("삼중 비교 < 0? {}", order < 0);

    auto quiet{ [](int x) { return x <= 7; } };
    std::println("all_of {} any_of(>=7) {} none_of(<0) {}",
                 std::all_of(first, last, quiet),
                 std::any_of(first, last, [](int x) { return x >= 7; }),
                 std::none_of(first, last, [](int x) { return x < 0; }));

    // 세기
    int limit{ 4 };
    int calls{ 0 };
    auto loud{ std::count_if(first, last, [limit, &calls](int x) {
        ++calls;
        return x > limit;
    }) };
    std::println("{}보다 큰 등급 {}개 (람다 {}번 호출), 6은 {}개", limit, loud,
                 calls, std::count(first, last, 6));
}
