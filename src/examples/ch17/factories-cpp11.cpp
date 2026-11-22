#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// 범위 팩토리와 ranges::to(C++20/23)가 없으므로
// iota 알고리즘(C++11), 반복문, 반복자 범위 생성자를 쓴다.
int main()
{
    std::vector<int> oneToFive(5);
    std::iota(oneToFive.begin(), oneToFive.end(), 1);    // 1 2 3 4 5

    std::vector<int> ids;                    // 무한 수열 대신 반복문
    for (int n = 100; ids.size() < 4; ++n) {
        if (n % 7 == 0) { ids.push_back(n); }
    }

    std::vector<int> readings;
    int r;
    while (std::cin >> r && r >= 0) { readings.push_back(r); }
    std::set<int> sorted(readings.begin(), readings.end());   // to<set> 대신

    std::istringstream line("거실 부엌 침실");   // split 대신
    std::vector<std::string> words((std::istream_iterator<std::string>(line)),
                                   std::istream_iterator<std::string>());

    std::cout << ids[0] << ' ' << oneToFive.back() << ' ' << sorted.size()
              << ' ' << words.size() << '\n';
}
