#include <iostream>
#include <map>
#include <random>
#include <string>

// 분포는 모두 C++11부터 있다. 구조적 바인딩(C++17), erase_if(C++20),
// println(C++23)이 없으므로 first/second와 cout을 쓴다.
int main()
{
    std::mt19937 engine(7);
    std::normal_distribution<double> normal(10.0, 2.0);
    std::map<int, int> bell;
    for (int i = 0; i < 100000; ++i) {
        ++bell[static_cast<int>(normal(engine) + 0.5)];
    }
    for (std::map<int, int>::const_iterator it = bell.begin();
         it != bell.end(); ++it) {
        if (it->first >= 6 && it->first <= 14) {
            std::cout << it->first << ' '
                      << std::string(it->second / 1000, '#') << '\n';
        }
    }
}
