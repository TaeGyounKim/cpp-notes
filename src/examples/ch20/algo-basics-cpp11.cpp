#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// if 초기화문(C++17), span(C++20), 투명 연산자(C++14), 캡처 표현식(C++14)이
// 없으므로 반복자 변수를 따로 두고, multiplies<int>와 바깥 변수를 쓴다.
bool isFever(double t) { return t >= 37.5; }

int main()
{
    std::vector<double> temps;
    double t;
    while (std::cin >> t && t != 0) { temps.push_back(t); }

    std::vector<double>::const_iterator it =
        std::find_if(temps.begin(), temps.end(), isFever);
    if (it != temps.end()) { std::cout << "첫 발열 " << *it << '\n'; }

    double sum = std::accumulate(temps.begin(), temps.end(), 0.0);
    std::vector<int> g = { 2, 8 };
    int product = std::accumulate(g.begin(), g.end(), 1,
                                  std::multiplies<int>());

    int calls = 0;   // 참조로 캡처해 람다가 복사돼도 같은 변수를 센다.
    auto counted = [&calls](double x) { ++calls; return x >= 37.5; };
    it = std::find_if(temps.begin(), temps.end(), counted);
    std::cout << sum / temps.size() << ' ' << std::pow(product, 0.5) << ' '
              << calls << ' ' << *it << '\n';
}
