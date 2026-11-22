#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// 어댑터 셋은 C++98부터 있다. 우주선 연산자(C++20)가 없으므로
// operator<를 직접 정의하고, emplace(C++11)로 제자리에 만든다.
struct Alert
{
    int level;
    std::string text;
    Alert(int l, std::string t) : level(l), text(std::move(t)) {}
};

bool operator<(const Alert& a, const Alert& b) { return a.level < b.level; }

int main()
{
    std::queue<std::string> jobs;
    jobs.push("보고서");
    jobs.push("영수증");
    std::cout << jobs.front() << ' ';
    jobs.pop();

    std::priority_queue<Alert> alerts;
    alerts.emplace(2, "디스크 80%");
    alerts.emplace(9, "전원 이상");
    std::cout << alerts.top().text << ' ';

    std::priority_queue<int, std::vector<int>, std::greater<int>> soonest;
    soonest.push(30);
    soonest.push(5);
    std::cout << soonest.top() << ' ';

    std::stack<std::string, std::vector<std::string>> undo;
    undo.push("굵게");
    undo.push("삭제");
    std::cout << undo.top() << '\n';
}
