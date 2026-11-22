#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 기본 ==(C++20)이 없으므로 직접 쓰고, 해시는 함수 객체를 템플릿 인수로 준다.
// flat_map(C++23) 대신 정렬된 vector와 lower_bound로 찾는다.
struct Cell
{
    int row;
    int col;
};

bool operator==(const Cell& a, const Cell& b)
{
    return a.row == b.row && a.col == b.col;
}

struct CellHash
{
    std::size_t operator()(const Cell& c) const
    {
        std::size_t h = std::hash<int>()(c.row);
        return h ^ (std::hash<int>()(c.col) + 0x9e3779b9 + (h << 6) + (h >> 2));
    }
};

int main()
{
    std::unordered_map<Cell, char, CellHash> board;
    board[Cell{ 1, 2 }] = 'O';
    std::cout << board[Cell{ 1, 2 }] << ' ' << board.count(Cell{ 2, 2 }) << ' ';

    typedef std::pair<std::string, int> Score;
    std::vector<Score> scores = { { "민수", 95 }, { "하늘", 82 } };  // 정렬됨
    Score key("지은", 0);
    auto pos = std::lower_bound(scores.begin(), scores.end(), key,
        [](const Score& a, const Score& b) { return a.first < b.first; });
    scores.insert(pos, Score("지은", 88));    // 정렬을 유지하며 넣음
    for (const auto& s : scores) { std::cout << s.first << s.second << ' '; }
    std::cout << '\n';
}
