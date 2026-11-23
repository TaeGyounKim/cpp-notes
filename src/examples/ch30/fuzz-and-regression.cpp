#include <map>
#include <optional>
#include <print>
#include <random>
#include <string>

// 시험 대상: "키=값" 줄들로 된 설정 텍스트.
// '=', '\\'는 앞에 '\\'를 붙이고, 줄바꿈은 "\\n"으로 쓴다.
using Settings = std::map<std::string, std::string>;

std::string escape(const std::string& s)
{
    std::string out;
    for (char c : s) {
        if (c == '\\' || c == '=') { out += '\\'; out += c; }
        else if (c == '\n') { out += "\\n"; }
        else { out += c; }
    }
    return out;
}

std::string to_text(const Settings& s)
{
    std::string out;
    for (const auto& [k, v] : s) { out += escape(k) + '=' + escape(v) + '\n'; }
    return out;
}

// 잘못된 입력이면 nullopt. 어떤 입력에도 죽거나 범위 밖을 읽으면 안 된다.
std::optional<Settings> from_text(const std::string& text)
{
    Settings result;
    std::string key, value;
    std::string* cur{ &key };
    bool seen_eq{ false };
    for (std::size_t i{ 0 }; i < text.size(); ++i) {
        char c{ text[i] };
        if (c == '\\') {
            if (i + 1 >= text.size()) { return std::nullopt; }
            char n{ text[++i] };
            if (n == 'n') { *cur += '\n'; }
            else if (n == '\\' || n == '=') { *cur += n; }
            else { return std::nullopt; }
        } else if (c == '=') {
            if (seen_eq) { return std::nullopt; }
            seen_eq = true;
            cur = &value;
        } else if (c == '\n') {
            if (!seen_eq) { return std::nullopt; }
            result[key] = value;
            key.clear();
            value.clear();
            cur = &key;
            seen_eq = false;
        } else {
            *cur += c;
        }
    }
    // BUG-42: 마지막 줄에 줄바꿈이 없으면 그 줄을 조용히 버렸다.
    if (!key.empty() || seen_eq) { return std::nullopt; }
    return result;
}

int main()
{
    std::mt19937 rng{ 2024 };   // 시드를 고정해 실패를 재현할 수 있게
    std::uniform_int_distribution<int> len{ 0, 12 };
    const std::string alphabet{ "ab=\\\n" };
    std::uniform_int_distribution<std::size_t> pick{ 0, alphabet.size() - 1 };
    auto random_string{ [&] {
        std::string s(len(rng), ' ');
        for (char& c : s) { c = alphabet[pick(rng)]; }
        return s;
    } };

    // 1) 퍼징: 아무 문자열이나 넣어도 죽지 않고 판정을 내려야 한다.
    int accepted{ 0 }, rejected{ 0 };
    for (int i{ 0 }; i < 20'000; ++i) {
        if (from_text(random_string())) { ++accepted; } else { ++rejected; }
    }
    std::println("퍼징 2만 번: 받아들임 {}, 거부 {}", accepted, rejected);

    // 2) 성질 테스트: 무작위 설정을 글로 썼다가 읽으면 그대로여야 한다.
    int mismatches{ 0 };
    for (int i{ 0 }; i < 5'000; ++i) {
        Settings s;
        for (int k{ 0 }; k < 3; ++k) { s[random_string()] = random_string(); }
        auto back{ from_text(to_text(s)) };
        if (!back || *back != s) { ++mismatches; }
    }
    std::println("왕복 5천 번: 불일치 {}", mismatches);

    // 3) 회귀 테스트 BUG-42: 끝 줄바꿈이 없는 줄을 버리지 말고 거부해야 한다.
    bool ok{ !from_text("a=1\nb=2").has_value() };
    std::println("BUG-42 회귀 테스트: {}", ok ? "통과" : "실패");
}
