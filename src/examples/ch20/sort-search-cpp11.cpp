#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

// 투명 비교자(C++14), clamp(C++17), 구조적 바인딩(C++17)이 없으므로
// greater<int>, min/max 조합, .first/.second를 쓴다.
int main()
{
    std::vector<int> scores = { 72, 95, 58, 88, 64, 91, 77 };

    std::vector<int> pass, fail;
    std::partition_copy(scores.begin(), scores.end(), std::back_inserter(pass),
                        std::back_inserter(fail),
                        [](int s) { return s >= 70; });

    std::vector<int> work(scores);
    std::nth_element(work.begin(), work.begin() + 2, work.end(),
                     std::greater<int>());

    std::vector<int> sorted(scores);
    std::sort(sorted.begin(), sorted.end());
    sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), 80), 80);

    std::vector<int> monday = { 1, 3, 5, 7 };
    std::vector<int> tuesday = { 3, 4, 5 };
    std::vector<int> both;
    std::set_intersection(monday.begin(), monday.end(), tuesday.begin(),
                          tuesday.end(), std::back_inserter(both));

    auto mm = std::minmax_element(scores.begin(), scores.end());
    int clamped = std::min(std::max(105, 0), 100);
    std::cout << pass.size() << ' ' << work[2] << ' ' << sorted[4] << ' '
              << both.size() << ' ' << *mm.first << ' ' << *mm.second << ' '
              << clamped << '\n';
}
