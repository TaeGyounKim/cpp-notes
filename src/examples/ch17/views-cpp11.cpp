#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// 뷰(C++20)가 없으므로 단계마다 임시 컨테이너를 만든다.
// 모든 원소를 그 자리에서 계산하므로 게으른 평가도 없다.
int main()
{
    std::vector<int> temps = { 18, 23, 21, 26, 19, 28, 24, 30 };

    std::vector<int> warm;                                  // filter
    std::copy_if(temps.begin(), temps.end(), std::back_inserter(warm),
                 [](int t) { return t >= 21; });
    std::vector<int> kelvin;                                // transform
    std::transform(warm.begin(), warm.end(), std::back_inserter(kelvin),
                   [](int t) { return t + 273; });
    std::vector<int> result(kelvin.begin() + 2, kelvin.end());   // drop(2)
    std::reverse(result.begin(), result.end());             // reverse

    for (int k : result) { std::cout << k << ' '; }
    std::cout << '\n';
}
