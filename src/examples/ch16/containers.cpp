#include <array>
#include <bitset>
#include <deque>
#include <flat_map>
#include <list>
#include <map>
#include <print>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

// span: vector, array, C 배열 무엇이든 받는 하나의 함수
double average(std::span<const double> values)
{
    double sum{ 0 };
    for (double v : values) { sum += v; }
    return values.empty() ? 0 : sum / values.size();
}

int main()
{
    // 순차 컨테이너
    std::vector<double> temps{ 21.5, 22.0, 23.5 };
    temps.push_back(24.0);                    // 끝에 넣기는 빠르다.
    std::array<double, 3> fixed{ 1.0, 2.0, 3.0 };
    double raw[]{ 10.0, 20.0 };
    std::println("평균 {} {} {}", average(temps), average(fixed), average(raw));

    std::deque<int> dq{ 2, 3 };
    dq.push_front(1);                         // 앞뒤 모두 빠르다.
    dq.push_back(4);
    std::list<int> linked{ 1, 3 };
    // 자리를 찾고 나면 끼워 넣기는 빠르다.
    linked.insert(std::next(linked.begin()), 2);
    std::println("deque {} list {}", dq, linked);

    // 컨테이너 어댑터
    std::queue<std::string> line;             // 먼저 온 쪽이 먼저(FIFO)
    line.push("1번 손님");
    line.push("2번 손님");
    std::stack<std::string> errors;           // 나중에 온 쪽이 먼저(LIFO)
    errors.push("오래된 오류");
    errors.push("최근 오류");
    std::priority_queue<int> urgent;          // 큰 값이 먼저
    for (int p : { 3, 9, 5 }) { urgent.push(p); }
    std::println("queue {} / stack {} / priority {}", line.front(),
                 errors.top(), urgent.top());

    // 정렬된 연관 컨테이너
    std::set<std::string> rooms{ "부엌", "거실", "부엌" };  // 중복 없이 정렬
    std::multiset<int> readings{ 3, 1, 3 };                // 중복 허용
    std::map<std::string, double> limits{ { "온도", 30 }, { "습도", 60 } };
    limits["기압"] = 1013;                                 // operator[]
    std::println("{} {} {}", rooms, readings, limits);

    // 해시 테이블(정렬하지 않음), C++23 평평한 맵(연속 메모리에 정렬)
    std::unordered_map<std::string, int> counts{ { "a", 1 }, { "b", 2 } };
    std::flat_map<int, std::string> codes{ { 3, "셋" }, { 1, "하나" } };
    std::println("unordered size {} / flat_map {}", counts.size(), codes);

    // 비트 집합
    std::bitset<10> flags;
    flags.set(1).set(4);
    std::println("{} (켜진 비트 {}개)", flags.to_string(), flags.count());
}
