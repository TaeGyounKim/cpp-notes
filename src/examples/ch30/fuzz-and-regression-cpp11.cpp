#include <cstdio>
#include <map>
#include <random>
#include <string>

// std::optional(C++17) 대신 bool 반환 + 출력 매개변수,
// 구조적 바인딩(C++17) 대신 반복자를 쓴다.
typedef std::map<std::string, std::string> Settings;

std::string escape(const std::string& s)
{
    std::string out;
    for (std::size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '\\' || c == '=') { out += '\\'; out += c; }
        else if (c == '\n') { out += "\\n"; }
        else { out += c; }
    }
    return out;
}

std::string to_text(const Settings& s)
{
    std::string out;
    for (Settings::const_iterator it = s.begin(); it != s.end(); ++it) {
        out += escape(it->first) + '=' + escape(it->second) + '\n';
    }
    return out;
}

bool from_text(const std::string& text, Settings& result)
{
    result.clear();
    std::string key, value;
    std::string* cur = &key;
    bool seen_eq = false;
    for (std::size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        if (c == '\\') {
            if (i + 1 >= text.size()) { return false; }
            char n = text[++i];
            if (n == 'n') { *cur += '\n'; }
            else if (n == '\\' || n == '=') { *cur += n; }
            else { return false; }
        } else if (c == '=') {
            if (seen_eq) { return false; }
            seen_eq = true;
            cur = &value;
        } else if (c == '\n') {
            if (!seen_eq) { return false; }
            result[key] = value;
            key.clear();
            value.clear();
            cur = &key;
            seen_eq = false;
        } else {
            *cur += c;
        }
    }
    return key.empty() && !seen_eq;
}

int main()
{
    std::mt19937 rng(2024);
    std::uniform_int_distribution<int> len(0, 12);
    const std::string alphabet = "ab=\\\n";
    std::uniform_int_distribution<std::size_t> pick(0, alphabet.size() - 1);

    int mismatches = 0;
    for (int i = 0; i < 5000; ++i) {
        Settings s;
        for (int k = 0; k < 3; ++k) {
            std::string key(len(rng), ' '), value(len(rng), ' ');
            for (std::size_t j = 0; j < key.size(); ++j) {
                key[j] = alphabet[pick(rng)];
            }
            for (std::size_t j = 0; j < value.size(); ++j) {
                value[j] = alphabet[pick(rng)];
            }
            s[key] = value;
        }
        Settings back;
        if (!from_text(to_text(s), back) || back != s) { ++mismatches; }
    }
    Settings dummy;
    std::printf("round trip mismatches: %d\n", mismatches);
    std::printf("BUG-42: %s\n", from_text("a=1\nb=2", dummy) ? "fail" : "pass");
}
