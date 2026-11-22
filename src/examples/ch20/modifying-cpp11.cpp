#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// std::erase_if(C++20) 대신 지우기-제거 관용구를 쓴다.
// generate, transform, copy_if, copy_n, replace_if 등은 C++11에서도 된다.
void show(const std::vector<int>& v)
{
    for (int x : v) { std::cout << x << ' '; }
    std::cout << '\n';
}

int main()
{
    std::vector<int> doubling(6);
    int seed = 1;
    std::generate(doubling.begin(), doubling.end(),
                  [&seed] { return seed *= 2; });
    show(doubling);

    std::vector<int> readings = { 5, 12, 7, 18, 3 };
    std::vector<int> high(readings.size());
    auto copiedEnd = std::copy_if(readings.begin(), readings.end(),
                                  high.begin(), [](int r) { return r >= 7; });
    high.erase(copiedEnd, high.end());
    show(high);

    std::vector<std::string> notes = { "", "점검", "", "교체" };
    notes.erase(std::remove_if(notes.begin(), notes.end(),
                               [](const std::string& s) { return s.empty(); }),
                notes.end());
    std::cout << notes.size() << ' ' << notes[0] << '\n';
}
