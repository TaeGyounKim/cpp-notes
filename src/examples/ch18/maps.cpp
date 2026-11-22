#include <map>
#include <print>
#include <string>
#include <utility>
#include <vector>

using namespace std::string_literals;

// const map에서는 operator[]를 쓸 수 없다. find()나 at()을 쓴다.
int stockOf(const std::map<std::string, int>& stock, const std::string& item)
{
    // return stock[item];               // 오류: operator[]는 const가 아님
    auto it{ stock.find(item) };
    return it != stock.end() ? it->second : 0;
}

int main()
{
    // pair: 두 값을 묶는다. 비교는 first 다음 second
    std::pair<std::string, int> a{ "사과", 3 };
    std::pair b{ "사과"s, 5 };                   // 인수 추론: pair<string, int>
    auto c{ std::make_pair("배"s, 1) };           // C++17 이전 방식
    std::println("{} < {}? {}  {} < {}? {}", a, b, a < b, c, a, c < a);

    // map: 키로 정렬된 키-값 쌍
    std::map<std::string, int> stock{ { "사과", 3 }, { "배", 7 } };

    // insert는 이미 있는 키의 값을 덮어쓰지 않는다.
    if (auto [it, inserted]{ stock.insert({ "사과", 10 }) }; !inserted) {
        std::println("사과는 이미 있음: {}개", it->second);
    }
    auto [pos, isNew]{ stock.insert_or_assign("사과", 10) };   // 덮어씀
    std::println("insert_or_assign: 새로 넣음? {} 값 {}", isNew, pos->second);

    stock["귤"] = 4;                             // 없으면 만들고 대입
    stock["배"] += 1;                            // 있으면 값을 고침
    stock.try_emplace("감", 2);                  // 없을 때만 제자리 생성
    stock.try_emplace("귤", 99);                 // 이미 있으므로 아무 일 없음
    stock.insert_range(std::vector<std::pair<std::string, int>>{
        { "딸기", 6 }, { "감", 50 } });          // C++23. 감은 이미 있어 무시
    std::println("{}", stock);

    // 훑기: 원소는 pair<const 키, 값>
    for (auto& [name, count] : stock) {
        count *= 2;                              // 값은 고칠 수 있다.
        // name += "!";                          // 오류: 키는 const
    }

    // 찾기
    std::println("배 {}개, 수박 {}개", stockOf(stock, "배"),
                 stockOf(stock, "수박"));
    std::println("contains(귤) {} count(귤) {} at(감) {}", stock.contains("귤"),
                 stock.count("귤"), stock.at("감"));
    int melon{ stock["수박"] };                 // 읽기만 해도 생긴다.
    std::println("수박 {}, 크기 {}", melon, stock.size());
    stock.erase("수박");                         // 키로 지우기

    // 노드 옮기기: 복사도 이동도 없이 다른 map으로
    std::map<std::string, int> sold;
    sold.insert(stock.extract("딸기"));
    std::map<std::string, int> extra{ { "배", 1 }, { "자두", 9 } };
    stock.merge(extra);                          // 겹치는 "배"는 extra에 남음
    std::println("stock {}\nsold {} extra {}", stock, sold, extra);
}
