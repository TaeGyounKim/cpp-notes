#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

// vector의 기본 기능은 C++98부터, 초기화 리스트는 C++11부터 있다.
// 클래스 템플릿 인수 추론(C++17), 컨테이너 출력(C++23)이 없으므로
// 타입을 적고 반복문으로 출력한다.
void show(const std::vector<int>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i) { std::cout << v[i] << ' '; }
    std::cout << '\n';
}

int main()
{
    std::vector<double> scores;
    double value;
    while (std::cin >> value && value >= 0) { scores.push_back(value); }
    if (scores.empty()) { return 0; }
    double top = *std::max_element(scores.begin(), scores.end());
    for (auto& s : scores) { s = s / top * 100; }
    std::cout << scores.front() << ' ' << scores.back() << '\n';

    try {
        std::cout << scores.at(scores.size()) << '\n';
    } catch (const std::out_of_range&) {
        std::cout << "at()이 예외를 던짐\n";
    }

    std::vector<int> a(3, 7);
    std::vector<int> b = { 3, 7 };
    a.swap(b);
    show(a);
    show(b);
    std::cout << std::boolalpha << (a < b) << '\n';
}
