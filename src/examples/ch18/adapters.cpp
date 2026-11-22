#include <compare>
#include <cstddef>
#include <functional>
#include <list>
#include <print>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

// 인쇄 대기열: 먼저 들어온 작업부터, 정해진 수까지만 받는다.
template <typename Job>
class PrintSpooler
{
public:
    explicit PrintSpooler(std::size_t limit) : m_limit{ limit } {}

    bool submit(const Job& job)
    {
        if (m_jobs.size() == m_limit) { return false; }   // 가득 참
        m_jobs.push(job);
        return true;
    }

    Job next()
    {
        if (m_jobs.empty()) { throw std::out_of_range{ "대기열이 비었음" }; }
        Job job{ m_jobs.front() };      // pop()은 돌려주지 않으므로 먼저 꺼냄
        m_jobs.pop();
        return job;
    }

private:
    std::queue<Job> m_jobs;             // 기본 바탕 컨테이너는 deque
    std::size_t m_limit;
};

// 우선순위가 있는 알림. <=>로 비교하면 priority_queue가 쓰는 <가 생긴다.
struct Alert
{
    int level;
    std::string text;
    auto operator<=>(const Alert& other) const { return level <=> other.level; }
};

int main()
{
    PrintSpooler<std::string> spooler{ 2 };
    for (const char* doc : { "보고서", "영수증", "포스터" }) {
        if (!spooler.submit(doc)) { std::println("{} 거절(가득 참)", doc); }
    }
    auto first{ spooler.next() };       // 인수 평가 순서는 정해지지 않으므로
    auto second{ spooler.next() };      // 따로 꺼낸다.
    std::println("인쇄 {} → {}", first, second);

    // priority_queue: 가장 "큰" 원소가 맨 위
    std::priority_queue<Alert> alerts;
    alerts.push({ 2, "디스크 80%" });
    alerts.push({ 9, "전원 이상" });
    alerts.push({ 5, "온도 높음" });
    while (!alerts.empty()) {
        std::print("[{}] {}  ", alerts.top().level, alerts.top().text);
        alerts.pop();
    }
    std::println("");

    // 비교자를 바꾸면 가장 작은 원소가 맨 위(최소 힙)
    std::priority_queue<int, std::vector<int>, std::greater<int>> soonest;
    for (int minutes : { 30, 5, 12 }) { soonest.push(minutes); }
    std::println("가장 가까운 일정 {}분 뒤", soonest.top());

    // stack: 나중에 넣은 것이 먼저(되돌리기 기록)
    std::stack<std::string, std::vector<std::string>> undo;   // 바탕 vector
    undo.push("글자 입력");
    undo.push("굵게");
    undo.push("삭제");
    std::print("되돌리기:");
    while (!undo.empty()) {
        std::print(" {}", undo.top());
        undo.pop();
    }
    std::println("");

    // C++23: 반복자 쌍 생성자, push_range, 출력
    std::vector<int> waiting{ 7, 8 };
    std::queue<int, std::list<int>> line(waiting.begin(), waiting.end());
    line.push_range(std::vector{ 9, 10 });
    std::println("줄 {} 맨 앞 {} 맨 뒤 {}", line, line.front(), line.back());
}
