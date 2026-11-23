#include <algorithm>
#include <chrono>
#include <cstdint>
#include <map>
#include <print>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 아주 작은 "수동 프로파일러": 구간마다 걸린 시간을 모은다.
class Sections {
public:
    class Scope {
    public:
        Scope(Sections& s, std::string name)
            : m_s{ s }, m_name{ std::move(name) },
              m_start{ std::chrono::steady_clock::now() } {}
        ~Scope()
        {
            auto spent{ std::chrono::steady_clock::now() - m_start };
            m_s.m_total[m_name] += spent;
            ++m_s.m_calls[m_name];
        }

    private:
        Sections& m_s;
        std::string m_name;
        std::chrono::steady_clock::time_point m_start;
    };

    void report() const
    {
        using ms = std::chrono::duration<double, std::milli>;
        double all{ 0 };
        for (const auto& [name, t] : m_total) { all += ms{ t }.count(); }
        for (const auto& [name, t] : m_total) {
            double v{ ms{ t }.count() };
            std::println("{:>14} {:6} 회 {:9.2f} ms {:5.1f}%", name,
                         m_calls.at(name), v, 100 * v / all);
        }
    }

private:
    std::map<std::string, std::chrono::steady_clock::duration> m_total;
    std::map<std::string, int> m_calls;
};

// 시험용 입력: 서로 다른 태그 800개가 섞인 6만 개
std::vector<std::string> make_tags()
{
    std::vector<std::string> tags;
    std::uint32_t x{ 12345 };
    for (int i{ 0 }; i < 60'000; ++i) {
        x = x * 1664525u + 1013904223u;            // 간단한 의사 난수
        tags.push_back("tag" + std::to_string(x % 800));
    }
    return tags;
}

// 1차 설계: vector에서 선형 탐색
std::size_t count_with_vector(const std::vector<std::string>& tags)
{
    std::vector<std::pair<std::string, int>> counts;
    for (const auto& t : tags) {
        auto it{ std::find_if(counts.begin(), counts.end(),
                              [&](const auto& e) { return e.first == t; }) };
        if (it != counts.end()) { ++it->second; }
        else { counts.emplace_back(t, 1); }
    }
    return counts.size();
}

// 2차 설계: 정렬된 map, O(log n) 탐색. operator[]로 한 줄에
std::size_t count_with_map(const std::vector<std::string>& tags)
{
    std::map<std::string, int> counts;
    for (const auto& t : tags) { ++counts[t]; }
    return counts.size();
}

// 3차 설계: 해시 테이블, 평균 O(1)
std::size_t count_with_hash(const std::vector<std::string>& tags)
{
    std::unordered_map<std::string, int> counts;
    for (const auto& t : tags) { ++counts[t]; }
    return counts.size();
}

int main()
{
    Sections prof;
    std::vector<std::string> tags;
    {
        Sections::Scope s{ prof, "make_tags" };
        tags = make_tags();
    }
    std::size_t a{}, b{}, c{};
    {
        Sections::Scope s{ prof, "vector" };
        a = count_with_vector(tags);
    }
    {
        Sections::Scope s{ prof, "map" };
        b = count_with_map(tags);
    }
    {
        Sections::Scope s{ prof, "unordered_map" };
        c = count_with_hash(tags);
    }
    std::println("서로 다른 태그: {} {} {}", a, b, c);
    prof.report();
}
