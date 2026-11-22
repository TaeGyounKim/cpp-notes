#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include <vector>

typedef std::list<std::string> Names;

// append_range(C++23) 대신 범위 insert, 컨테이너 출력(C++23) 대신 반복문.
// deque, list, array, forward_list는 C++11에서도 그대로 쓴다.
Names roster(const std::vector<Names>& classes, const Names& withdrawn)
{
    Names all;
    for (const auto& c : classes) {
        all.insert(all.end(), c.begin(), c.end());
    }
    all.sort();
    all.unique();
    for (const auto& name : withdrawn) { all.remove(name); }
    return all;
}

int main()
{
    std::deque<int> recent = { 2, 3 };
    recent.push_front(1);
    std::cout << recent.front() << ' ';

    Names names = roster({ { "하늘", "민수" }, { "지은", "민수" } },
                         { "지은" });
    for (const auto& n : names) { std::cout << n << ' '; }

    std::forward_list<int> a = { 5, 6 };
    std::forward_list<int> b = { 1, 2 };
    a.splice_after(a.before_begin(), b);
    for (int x : a) { std::cout << x; }

    std::array<int, 3> fixed = {{ 9, 8, 7 }};    // C++11은 이중 중괄호가 안전
    fixed.fill(3);
    std::cout << ' ' << std::get<1>(fixed) << '\n';
}
