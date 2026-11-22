#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::string>& values)
{
    for (const auto& value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> names{ "Park", "Kim", "Lee", "Choi" };

    // std::ranges::sort(C++20) 대신 반복자 두 개를 받는 std::sort
    std::sort(names.begin(), names.end());
    print(names);

    // 정렬 기준은 람다로 넘긴다.
    std::sort(names.begin(), names.end(),
              [](const std::string& a, const std::string& b) {
                  return a.size() < b.size();
              });
    print(names);
}
