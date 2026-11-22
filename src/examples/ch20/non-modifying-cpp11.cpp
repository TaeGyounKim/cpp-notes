#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

// equal·mismatch의 반복자 넷 판(C++14), 보이어-무어 탐색기(C++17),
// 구조적 바인딩(C++17), 삼중 비교(C++20)가 없으므로 반복자 셋 판과
// .first/.second를 쓴다. 반복자 셋 판은 두 번째 범위가 충분히 길어야 한다.
int main()
{
    std::vector<int> levels = { 3, 4, 7, 6, 6, 2 };
    std::vector<int>::const_iterator first = levels.begin();
    std::vector<int>::const_iterator last = levels.end();

    std::cout << *std::find_if_not(first, last, [](int x) { return x < 5; })
              << ' ' << *std::adjacent_find(first, last) << ' '
              << std::search_n(first, last, 2, 6) - first << '\n';

    std::list<int> other = { 3, 4, 9, 1, 1, 1 };       // levels보다 길게
    auto miss = std::mismatch(first, last, other.begin());
    std::cout << *miss.first << " vs " << *miss.second << ' '
              << std::count_if(first, last, [](int x) { return x > 4; })
              << '\n';
}
