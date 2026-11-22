#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <print>
#include <string>
#include <vector>

// 여러 수업의 수강생 목록을 합쳐 중복과 철회한 학생을 뺀 명단을 만든다.
using Names = std::list<std::string>;

Names roster(const std::vector<Names>& classes, const Names& withdrawn)
{
    Names all;
    for (const auto& c : classes) { all.append_range(c); }   // C++23
    all.sort();                                 // list 전용 정렬(안정)
    all.unique();                               // 이웃한 중복 제거
    for (const auto& name : withdrawn) { all.remove(name); }
    return all;
}

int main()
{
    // deque: 앞뒤 모두 상수 시간에 넣고 뺀다.
    std::deque<int> recent{ 2, 3 };
    recent.push_front(1);
    recent.push_back(4);
    recent.pop_front();
    std::println("deque {}", recent);

    // list: 임의 접근은 없고 양방향 반복자만
    std::list<std::string> words{ "가방", "다리" };
    auto it{ words.begin() };
    ++it;                                       // it + 1은 안 됨
    words.insert(it, "나무");                   // 자리를 찾으면 상수 시간
    std::list<std::string> more{ "라면", "마당" };
    words.splice(words.end(), more);            // 노드를 통째로 옮김
    std::println("list {} / more는 비었나? {}", words, more.empty());

    auto names{ roster({ { "하늘", "민수" }, { "지은", "민수" }, { "도윤" } },
                       { "지은" }) };
    std::println("명단 {}", names);

    // forward_list: 앞으로만. 변경은 "다음"에 한다.
    std::forward_list<int> a{ 5, 6 };
    std::forward_list<int> b{ 1, 2 };
    a.splice_after(a.before_begin(), b);        // b를 맨 앞에
    a.push_front(0);
    a.insert_after(a.begin(), 9);               // 0 다음에 9
    std::println("forward_list {}", a);

    // array: 크기가 고정된 C 배열 대용
    std::array<int, 3> fixed{ 9, 8, 7 };
    std::println("array {} 크기 {}", fixed, fixed.size());
    fixed.fill(3);
    std::println("fill 뒤 {} / get<1> {}", fixed, std::get<1>(fixed));
    // std::get<10>(fixed);                     // 컴파일 오류: 범위 밖
    [[maybe_unused]] std::array<int, 3> junk;   // 기본 타입은 초기화되지 않음
    std::array<int, 3> zeros{};                 // {}로 0 초기화
    std::println("zeros {}", zeros);

    double raw[]{ 1.5, 2.5 };
    auto converted{ std::to_array(raw) };       // C++20: array<double, 2>
    std::println("to_array {}", converted);
}
