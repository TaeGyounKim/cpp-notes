#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// 실행 정책·reduce·transform_reduce·scan(C++17), ranges(C++20)가 없으므로
// accumulate, inner_product, partial_sum을 쓴다. 모두 왼쪽부터 순차 실행이다.
int main()
{
    std::vector<int> a = { 1, 2, 3, 4 };
    std::vector<int> b = { 9, 8, 7, 6 };

    std::vector<int> ids(5);
    std::iota(ids.begin(), ids.end(), 1);                 // iota는 C++11

    int sum = std::accumulate(a.begin(), a.end(), 0);
    int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    int squares = std::inner_product(a.begin(), a.end(), a.begin(), 0);

    std::vector<int> running(a.size());
    std::partial_sum(a.begin(), a.end(), running.begin());   // 누적 합

    std::cout << ids.back() << ' ' << sum << ' ' << dot << ' ' << squares
              << ' ' << running.back() << '\n';
}
