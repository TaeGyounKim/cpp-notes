#include <cstdio>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

// std::optional(C++17) 대신 bool 반환 + 출력 매개변수,
// std::println(C++23) 대신 printf
class ScoreSheet {
public:
    explicit ScoreSheet(const std::string& line)
    {
        std::istringstream in(line);
        in >> m_player;
        m_scores.assign(std::istream_iterator<int>(in),
                        std::istream_iterator<int>());
    }

    const std::string& player() const { return m_player; }
    bool average(double& out) const
    {
        if (m_scores.empty()) { return false; }
        double sum = std::accumulate(m_scores.begin(), m_scores.end(), 0.0);
        out = sum / static_cast<double>(m_scores.size());
        return true;
    }

private:
    std::string m_player;
    std::vector<int> m_scores;
};

void report(const ScoreSheet& sheet)
{
    double avg = 0;
    if (sheet.average(avg)) {
        std::printf("%s: %.2f\n", sheet.player().c_str(), avg);
    } else {
        std::printf("%s: no scores\n", sheet.player().c_str());
    }
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) { continue; }
        ScoreSheet sheet(line);
        report(sheet);
    }
}
