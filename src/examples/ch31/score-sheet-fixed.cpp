#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <print>
#include <sstream>
#include <string>
#include <vector>

// 고친 판: 원시 배열 대신 vector(0의 규칙), 실수 나눗셈, 빈 점수 처리
class ScoreSheet {
public:
    explicit ScoreSheet(const std::string& line)
    {
        std::istringstream in{ line };
        in >> m_player;
        m_scores.assign(std::istream_iterator<int>{ in },
                        std::istream_iterator<int>{});
    }

    const std::string& player() const { return m_player; }
    std::optional<double> average() const
    {
        if (m_scores.empty()) { return std::nullopt; }
        double sum{ std::accumulate(m_scores.begin(), m_scores.end(), 0.0) };
        return sum / static_cast<double>(m_scores.size());
    }

private:
    std::string m_player;
    std::vector<int> m_scores;   // 복사·이동·소멸을 알아서
};

void report(const ScoreSheet& sheet)
{
    if (auto avg{ sheet.average() }) {
        std::println("{}: 평균 {:.2f}", sheet.player(), *avg);
    } else {
        std::println("{}: 점수 없음", sheet.player());
    }
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) { continue; }
        ScoreSheet sheet{ line };
        report(sheet);
        ScoreSheet copy{ sheet };   // 복사해도 안전
        report(copy);
    }
}
