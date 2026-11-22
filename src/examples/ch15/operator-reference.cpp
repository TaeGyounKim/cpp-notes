#include <compare>
#include <print>
#include <string>
#include <utility>

class Label
{
public:
    explicit Label(std::string text) : m_text{ std::move(text) } {}
    const std::string& text() const { return m_text; }
    std::string take() && { return std::move(m_text); }   // 임시 객체에서 꺼냄

    // C++20: <=>을 기본으로 만들면 <, <=, >, >=가 모두 생긴다.
    // ==도 기본으로 만들면 !=는 컴파일러가 알아서 쓴다.
    auto operator<=>(const Label&) const = default;
    bool operator==(const Label&) const = default;

private:
    std::string m_text;
};

// 우측값 참조 판: 임시 객체의 메모리를 다시 쓴다.
Label operator+(const Label& a, const Label& b)
{
    std::println("  (복사본을 만들어 이어 붙임)");
    return Label{ a.text() + b.text() };
}
Label operator+(Label&& a, const Label& b)
{
    std::println("  (왼쪽 임시 객체를 재사용)");
    std::string s{ std::move(a).take() };   // 문자열의 메모리를 옮겨 옴
    s += b.text();                          // 그 메모리에 이어 붙임
    return Label{ std::move(s) };
}

int main()
{
    Label a{ "온도" };
    Label b{ "센서" };
    Label c{ a + b };                    // 둘 다 좌측값
    Label d{ Label{ "실내" } + b };      // 왼쪽이 임시 객체
    std::println("{} {}", c.text(), d.text());

    std::println("a < b: {}, a != b: {}, a >= a: {}", a < b, a != b, a >= a);

    // 대체 표기: and, or, not 등은 키워드다.
    bool ok{ (a == a) and not (a == b) };
    std::println("대체 표기 결과 {}", ok);
}
