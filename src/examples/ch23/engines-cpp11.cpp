#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// <random>의 엔진과 분포는 C++11부터 있다.
// 범위 알고리즘(C++20)과 println(C++23)이 없으므로 반복자와 cout을 쓴다.
int main()
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> die(1, 6);

    std::vector<int> rolls(10);
    std::generate(rolls.begin(), rolls.end(),
                  [&]() { return die(engine); });
    for (int r : rolls) { std::cout << r << ' '; }
    std::cout << '\n';

    std::mt19937 fixed(2026);
    std::cout << fixed() << '\n';
}
