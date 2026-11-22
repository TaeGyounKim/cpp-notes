#include <print>
#include <regex>
#include <string>
#include <vector>

int main()
{
    const std::string log{ "kitchen=24.5; living=22.0, bedroom=19.5" };

    // regex_iterator: 모든 일치를 차례로. 역참조하면 smatch
    const std::regex pair{ R"((\w+)=([\d.]+))" };
    const std::sregex_iterator end;              // 기본 생성 = 끝
    for (std::sregex_iterator it{ log.cbegin(), log.cend(), pair }; it != end;
         ++it) {
        const std::smatch& m{ *it };
        std::print("[{} -> {}] ", m[1].str(), m[2].str());
    }
    std::println("");

    // regex_token_iterator: 원하는 그룹만 차례로(여기서는 2번 그룹 = 값)
    std::vector<std::string> values{
        std::sregex_token_iterator{ log.cbegin(), log.cend(), pair, 2 },
        std::sregex_token_iterator{} };
    std::println("값만 {}", values);

    // 그룹 여러 개: {1, 2}면 이름, 값, 이름, 값, ...
    std::vector<std::string> both{
        std::sregex_token_iterator{ log.cbegin(), log.cend(), pair, { 1, 2 } },
        std::sregex_token_iterator{} };
    std::println("이름과 값 {}", both);

    // -1: 일치하지 않는 부분을 훑는다(토큰화). 구분자 , ; 와 주변 공백
    const std::regex sep{ R"(\s*[,;]\s*)" };
    std::vector<std::string> fields{
        std::sregex_token_iterator{ log.cbegin(), log.cend(), sep, -1 },
        std::sregex_token_iterator{} };
    std::println("나눈 필드 {}", fields);

    // regex_replace: $1, $2로 그룹을, $&로 전체 일치를 가리킨다.
    std::println("{}", std::regex_replace(log, pair, "$1: $2도"));
    namespace rc = std::regex_constants;
    std::println("{}", std::regex_replace(log, pair, "<$&>",
                                          rc::format_first_only));
    std::println("{}", std::regex_replace(log, pair, "$1\n",
                                          rc::format_no_copy));
}
