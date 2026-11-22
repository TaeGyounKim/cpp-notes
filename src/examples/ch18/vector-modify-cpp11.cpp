#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void show(const std::vector<int>& v)
{
    for (int x : v) { std::cout << x << ' '; }
    std::cout << '\n';
}

// std::erase/erase_if(C++20), append_range(C++23)가 없으므로
// 지우기-제거 관용구(remove-erase idiom)와 범위 insert를 쓴다.
int main()
{
    std::vector<int> nums = { 1, 2, 3, 5 };
    nums.insert(nums.begin() + 3, 4);
    std::vector<int> more = { 6, 7 };
    nums.insert(nums.end(), more.begin(), more.end());
    nums.erase(nums.begin() + 1, nums.begin() + 3);
    nums.pop_back();
    show(nums);

    std::vector<int> temps = { 21, -99, 23, -99, 22 };
    temps.erase(std::remove(temps.begin(), temps.end(), -99), temps.end());
    temps.erase(std::remove_if(temps.begin(), temps.end(),
                               [](int t) { return t > 22; }),
                temps.end());
    show(temps);

    std::vector<std::string> names;
    std::string label(3, 'a');
    names.push_back(std::move(label));      // 이동(C++11)
    names.emplace_back(3, 'b');             // 제자리 생성(C++11)
    std::cout << names[0] << ' ' << names[1] << '\n';
}
