#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// 대부분의 컨테이너는 C++98부터, array·unordered_*는 C++11부터 있다.
// span(C++20), flat_map(C++23)이 없으므로 포인터와 길이를 넘긴다.
double average(const double* values, std::size_t n)
{
    double sum = 0;
    for (std::size_t i = 0; i < n; ++i) { sum += values[i]; }
    return n == 0 ? 0 : sum / n;
}

int main()
{
    std::vector<double> temps = { 21.5, 22.0, 23.5, 24.0 };
    std::array<double, 3> fixed = {{ 1.0, 2.0, 3.0 }};
    std::cout << average(temps.data(), temps.size()) << ' '
              << average(fixed.data(), fixed.size()) << '\n';

    std::priority_queue<int> urgent;
    urgent.push(3);
    urgent.push(9);
    std::set<std::string> rooms = { "부엌", "거실", "부엌" };
    std::map<std::string, double> limits;
    limits["기압"] = 1013;
    std::unordered_map<std::string, int> counts = { { "a", 1 } };
    std::bitset<10> flags;
    flags.set(1).set(4);
    std::cout << urgent.top() << ' ' << rooms.size() << ' ' << limits["기압"]
              << ' ' << counts.size() << ' ' << flags << '\n';
}
