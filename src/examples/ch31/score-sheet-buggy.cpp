#include <iostream>
#include <print>
#include <sstream>
#include <string>

// 버그가 있는 프로그램입니다. 따라 쓰지 마세요.
// 입력 한 줄: 선수 이름 뒤에 점수들. 예) Mina 90 85 88
class ScoreSheet {
public:
    explicit ScoreSheet(const std::string& line)
    {
        std::istringstream in{ line };
        in >> m_player;
        int score{ 0 };
        while (in >> score) { ++m_count; }          // 1차: 개수 세기
        m_scores = new int[m_count];
        in.clear();
        in.seekg(0);
        in >> m_player;
        for (int i{ 0 }; i < m_count; ++i) { in >> m_scores[i]; }   // 2차: 읽기
    }
    ScoreSheet(const ScoreSheet& other)
        : m_player{ other.m_player }, m_count{ other.m_count },
          m_scores{ other.m_scores } {}           // 포인터만 복사
    ~ScoreSheet() { delete[] m_scores; }

    const std::string& player() const { return m_player; }
    double average() const
    {
        int sum{ 0 };
        for (int i{ 0 }; i < m_count; ++i) { sum += m_scores[i]; }
        return sum / m_count;
    }

private:
    std::string m_player;
    int m_count{ 0 };
    int* m_scores{ nullptr };
};

void report(ScoreSheet sheet)   // 값으로 받음
{
    std::println("{}: 평균 {:.2f}", sheet.player(), sheet.average());
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) { continue; }
        ScoreSheet sheet{ line };
        report(sheet);
    }
}
