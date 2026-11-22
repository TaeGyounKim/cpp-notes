#include <cstddef>
#include <flat_map>
#include <flat_set>
#include <functional>
#include <print>
#include <string>
#include <unordered_map>
#include <unordered_set>

// 직접 만든 키 타입: ==가 있어야 하고, 해시 함수가 필요하다.
struct Cell
{
    int row;
    int col;
    bool operator==(const Cell&) const = default;   // C++20
};

// std::hash를 특수화한다(std에 특수화를 두는 것은 허용됨).
template <>
struct std::hash<Cell>
{
    std::size_t operator()(const Cell& c) const
    {
        // 두 멤버의 해시를 섞는다. 간단한 예일 뿐 좋은 해시는 더 정교하다.
        std::size_t h{ std::hash<int>{}(c.row) };
        return h ^ (std::hash<int>{}(c.col) + 0x9e3779b9 + (h << 6) + (h >> 2));
    }
};

int main()
{
    std::unordered_map<std::string, std::string> phone{
        { "민수", "010-1111" }, { "지은", "010-2222" } };
    phone.insert({ "하늘", "010-3333" });
    phone["도윤"] = "010-4444";
    phone.erase("지은");
    for (const auto& [name, number] : phone) {
        std::print("{}:{} ", name, number);
    }
    std::println("");                            // 순서는 정해지지 않음

    // 버킷 살펴보기
    std::size_t b{ phone.bucket("민수") };
    std::print("민수는 버킷 {}에 있고, 같은 버킷:", b);
    for (auto it{ phone.cbegin(b) }; it != phone.cend(b); ++it) {
        std::print(" {}", it->first);            // 지역 반복자
    }
    std::println("");
    std::println("버킷 {}개, 적재율 {:.2f}", phone.bucket_count(),
                 phone.load_factor());

    // 직접 만든 키
    std::unordered_map<Cell, char> board;
    board[{ 0, 0 }] = 'X';
    board[{ 1, 2 }] = 'O';
    std::println("(1,2)에 {}  (2,2) 있나? {}", board.at({ 1, 2 }),
                 board.contains({ 2, 2 }));

    std::unordered_set<int> seen{ 3, 1, 4, 1, 5 };   // 중복 없음, 정렬 안 됨
    std::println("seen 크기 {}", seen.size());

    // C++23 평평한 연관 컨테이너: 정렬된 vector 위의 어댑터
    std::flat_map<std::string, int> scores{ { "하늘", 82 }, { "민수", 95 } };
    scores["지은"] = 88;
    std::println("{}", scores);
    std::println("키들 {} / 값들 {}", scores.keys(), scores.values());
    std::flat_set<int> ids{ 30, 10, 20, 10 };
    std::println("{} / ids[1]은 반복자로 {}", ids, *(ids.begin() + 1));
}
