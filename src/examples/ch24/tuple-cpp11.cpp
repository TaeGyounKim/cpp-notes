#include <functional>
#include <iostream>
#include <string>
#include <tuple>

// tuple, get<번호>, make_tuple, tie, ignore, tuple_cat은 C++11부터 있다.
// get<타입>은 C++14, 구조적 바인딩·CTAD·apply는 C++17, tuple 출력은 C++23
std::tuple<std::string, int, bool> grade(const std::string& name, int score)
{
    return std::make_tuple(name, score, score >= 60);
}

struct Version {
    int major;
    int minor;
    std::string tag;
};

bool operator<(const Version& a, const Version& b)
{
    return std::tie(a.major, a.minor) < std::tie(b.major, b.minor);
}

int main()
{
    std::string name;
    int score = 0;
    bool pass = false;
    std::tie(name, score, pass) = grade("kim", 72);
    std::cout << name << ' ' << score << ' ' << pass << '\n';

    auto t = std::tuple_cat(std::make_tuple(1, 2.5), std::make_tuple('x'));
    std::cout << std::tuple_size<decltype(t)>::value << ' '
              << std::get<2>(t) << '\n';

    Version a = { 2, 3, "beta" };
    Version b = { 2, 4, "alpha" };
    std::cout << std::boolalpha << (a < b) << '\n';
}
