#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

// 대부분의 알고리즘은 C++98부터 있다. all_of, iota, minmax_element는 C++11,
// clamp는 C++17, ranges와 contains·fold_left는 C++20/23이다.
int main()
{
    std::vector<int> v = { 5, 3, 8, 3, 1, 9, 2 };
    std::cout << std::count(v.begin(), v.end(), 3) << ' '
              << std::all_of(v.begin(), v.end(), [](int x) { return x > 0; })
              << '\n';

    std::vector<int> sorted(v);
    std::sort(sorted.begin(), sorted.end());
    std::cout << std::binary_search(sorted.begin(), sorted.end(), 5) << ' '
              << *std::lower_bound(sorted.begin(), sorted.end(), 4) << '\n';

    std::set<int> a = { 1, 2, 3, 4 };
    std::set<int> b = { 3, 4, 5 };
    std::vector<int> both;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(both));

    std::vector<int> seq(5);
    std::iota(seq.begin(), seq.end(), 1);
    int clamped = std::min(std::max(15, 0), 10);   // clamp 대신
    std::cout << both.size() << ' '
              << std::accumulate(seq.begin(), seq.end(), 0) << ' ' << clamped
              << '\n';
}
