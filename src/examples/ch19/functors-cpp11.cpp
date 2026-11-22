#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// 투명 연산자(std::less<>, C++14), not_fn(C++17), bind_front(C++20)가 없으므로
// 타입을 적고, bind와 mem_fn(C++11)의 결과에 !를 직접 붙인다.
void announce(int floor, const std::string& room)
{
    std::cout << floor << "층 " << room << '\n';
}

void increment(int& n) { ++n; }

int main()
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> lowFirst;
    lowFirst.push(26);
    lowFirst.push(18);
    std::cout << lowFirst.top() << '\n';

    auto onThird = std::bind(announce, 3, std::placeholders::_1);
    onThird("회의실");

    int count = 0;
    std::bind(increment, std::ref(count))();

    auto isEmpty = std::mem_fn(&std::string::empty);
    std::string note = "점검";
    std::cout << count << ' ' << !isEmpty(note) << '\n';
}
