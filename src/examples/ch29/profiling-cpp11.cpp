#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 구조적 바인딩(C++17), 제네릭 람다(C++14), 숫자 구분자 1'000(C++14) 없이
typedef std::chrono::steady_clock Clock;

double ms_since(Clock::time_point start)
{
    return std::chrono::duration<double, std::milli>(Clock::now() - start)
        .count();
}

std::vector<std::string> make_tags()
{
    std::vector<std::string> tags;
    std::uint32_t x = 12345;
    for (int i = 0; i < 60000; ++i) {
        x = x * 1664525u + 1013904223u;
        tags.push_back("tag" + std::to_string(x % 800));
    }
    return tags;
}

struct SameKey {
    const std::string* key;
    bool operator()(const std::pair<std::string, int>& e) const
    {
        return e.first == *key;
    }
};

std::size_t count_with_vector(const std::vector<std::string>& tags)
{
    std::vector<std::pair<std::string, int> > counts;
    for (std::size_t i = 0; i < tags.size(); ++i) {
        SameKey same = { &tags[i] };
        std::vector<std::pair<std::string, int> >::iterator it =
            std::find_if(counts.begin(), counts.end(), same);
        if (it != counts.end()) { ++it->second; }
        else { counts.push_back(std::make_pair(tags[i], 1)); }
    }
    return counts.size();
}

template <typename Map>
std::size_t count_with(const std::vector<std::string>& tags)
{
    Map counts;
    for (std::size_t i = 0; i < tags.size(); ++i) { ++counts[tags[i]]; }
    return counts.size();
}

int main()
{
    std::vector<std::string> tags = make_tags();

    Clock::time_point t = Clock::now();
    std::size_t a = count_with_vector(tags);
    std::printf("vector        %zu %8.2f ms\n", a, ms_since(t));

    t = Clock::now();
    std::size_t b = count_with<std::map<std::string, int> >(tags);
    std::printf("map           %zu %8.2f ms\n", b, ms_since(t));

    t = Clock::now();
    std::size_t c = count_with<std::unordered_map<std::string, int> >(tags);
    std::printf("unordered_map %zu %8.2f ms\n", c, ms_since(t));
}
