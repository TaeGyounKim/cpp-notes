#include <print>
#include <regex>
#include <string>
#include <vector>

// 패턴 하나를 여러 입력에 맞춰 보고, 전체가 일치하는지 출력한다.
void check(const std::string& pattern, const std::vector<std::string>& inputs)
{
    std::regex re{ pattern };                   // 기본 문법: ECMAScript
    std::print("{:<22}", pattern);
    for (const auto& s : inputs) {
        std::print(" {}:{}", s, std::regex_match(s, re) ? "O" : "x");
    }
    std::println("");
}

int main()
{
    check(R"(a.c)", { "abc", "a5c", "ac", "ab5c" });          // 와일드카드
    check(R"(cat|dog)", { "cat", "dog", "cow" });             // 선택
    check(R"(a*b)", { "b", "aab", "ac" });                    // 0번 이상
    check(R"(a+b)", { "b", "ab", "aaab" });                   // 1번 이상
    check(R"(colou?r)", { "color", "colour", "colouur" });    // 0번 또는 1번
    check(R"(b{3,4})", { "bb", "bbb", "bbbb", "bbbbb" });     // 횟수 범위
    check(R"(ab+c|d)", { "abbc", "d", "abd" });               // 우선순위
    check(R"(ab+(?:c|d))", { "abbc", "abd", "d" });           // 괄호로 묶기
    check(R"(Room[1-3])", { "Room1", "Room3", "Room4" });     // 문자 집합
    check(R"([^0-9]+)", { "abc", "a1c" });                    // 집합의 부정
    check(R"([[:upper:]][[:lower:]]+)", { "Seoul", "seoul" }); // 문자 클래스
    check(R"(\d{3}-\d{4})", { "555-1234", "55-1234" });       // \d = 숫자
    check(R"((\d+)-.*-\1)", { "12-ab-12", "12-ab-21" });      // 역참조
    check(R"(\w+@\w+\.com)", { "kim@mail.com", "kim@mail.net" });

    // 탐욕적 대 탐욕적이지 않은 수량자: 하위 일치를 비교
    std::smatch m;
    std::string text{ "aaabbb" };
    std::regex_match(text, m, std::regex{ R"((a+)(ab)*(b+))" });
    std::println("탐욕적      \"{}\" \"{}\" \"{}\"", m[1].str(), m[2].str(),
                 m[3].str());
    std::regex_match(text, m, std::regex{ R"((a+?)(ab)*(b+))" });
    std::println("탐욕적 아님 \"{}\" \"{}\" \"{}\"", m[1].str(), m[2].str(),
                 m[3].str());

    // 전방 탐색: 소문자, 대문자, 구두점이 하나씩 있고 8자 이상
    std::regex strong{
        R"((?=.*[[:lower:]])(?=.*[[:upper:]])(?=.*[[:punct:]]).{8,})" };
    for (std::string pw : { "Passw0rd!", "password", "Ab!" }) {
        bool ok{ std::regex_match(pw, strong) };
        std::print("{}:{} ", pw, ok ? "강함" : "약함");
    }
    std::println("");

    // 날 문자열 리터럴이 없으면 역슬래시를 두 번 써야 한다.
    std::regex same1{ "\\d+\\.\\d+" };
    std::regex same2{ R"(\d+\.\d+)" };
    std::println("{} {}", std::regex_match("3.14", same1),
                 std::regex_match("3.14", same2));
}
