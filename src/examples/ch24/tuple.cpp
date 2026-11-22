#include <functional>
#include <print>
#include <string>
#include <tuple>

// 여러 값을 한 번에 돌려준다: 이름, 점수, 합격 여부
std::tuple<std::string, int, bool> grade(std::string name, int score)
{
    return { name, score, score >= 60 };
}

struct Version {
    int major;
    int minor;
    std::string tag;   // 비교에서 뺄 멤버
    // tie로 major, minor만 사전식으로 비교한다.
    auto operator<=>(const Version& rhs) const
    {
        return std::tie(major, minor) <=> std::tie(rhs.major, rhs.minor);
    }
    bool operator==(const Version& rhs) const
    {
        return std::tie(major, minor) == std::tie(rhs.major, rhs.minor);
    }
};

int area(int w, int h) { return w * h; }

int main()
{
    std::tuple t{ 7, std::string{ "seven" }, 7.5 };      // CTAD
    std::println("{} / {} {} {}", t, std::get<0>(t), std::get<std::string>(t),
                 std::get<2>(t));
    std::println("크기 {}", std::tuple_size_v<decltype(t)>);

    // 구조적 바인딩과 tie로 분해하기
    auto [name, score, pass] { grade("kim", 72) };
    std::println("{} {} {}", name, score, pass);
    int s2{ 0 };
    bool p2{ false };
    std::tie(std::ignore, s2, p2) = grade("lee", 41);    // 이름은 버린다.
    std::println("{} {}", s2, p2);

    // 참조를 담기: ref, cref
    double rate{ 1.5 };
    // 타입은 tuple<double&, const double&>
    std::tuple refs{ std::ref(rate), std::cref(rate) };
    std::get<0>(refs) *= 2;
    std::println("rate {}", rate);

    // 이어 붙이기, 비교
    auto joined{ std::tuple_cat(t, std::tuple{ 'x', true }) };
    std::println("{}", joined);
    // 앞 원소부터 차례로 비교(사전식). 문자열은 std::string으로 담는다.
    using namespace std::string_literals;
    std::println("{}", std::tuple{ 1, "b"s } < std::tuple{ 1, "c"s });

    Version v1{ 2, 3, "beta" };
    Version v2{ 2, 3, "release" };
    std::println("v1 == v2? {} (tag는 비교 안 함)", v1 == v2);

    // apply, make_from_tuple
    std::println("넓이 {}", std::apply(area, std::tuple{ 4, 5 }));
    auto v3{ std::make_from_tuple<Version>(std::tuple{ 3, 0, "rc" }) };
    std::println("{}.{}-{}", v3.major, v3.minor, v3.tag);
}
