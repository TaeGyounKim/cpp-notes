#include <print>
#include <string>
#include <utility>

class Label
{
public:
    explicit Label(std::string text) : m_text{ std::move(text) } {}

    // &: 이름 있는 객체(좌측값)에서 부를 때
    const std::string& text() const&
    {
        std::println("  (& 판: 참조를 돌려줌)");
        return m_text;
    }
    // &&: 임시 객체(우측값)에서 부를 때. 곧 사라질 테니 문자열을 옮겨 준다.
    std::string&& text() &&
    {
        std::println("  (&& 판: 옮겨 줌)");
        return std::move(m_text);
    }

    // 대입은 좌측값에만 허락한다.
    Label& operator=(const std::string& rhs) &
    {
        m_text = rhs;
        return *this;
    }

private:
    std::string m_text;
};

Label makeLabel() { return Label{ "임시 라벨" }; }

int main()
{
    Label kitchen{ "부엌" };
    std::println("{}", kitchen.text());

    std::string taken{ Label{ "거실" }.text() };   // 임시 객체에서 옮겨 받음
    std::println("{}", taken);

    kitchen = "주방";        // 좌측값에 대입: 됨
    // makeLabel() = "헛일";  // 컴파일 오류: 임시 객체에 대입
    std::println("{}", kitchen.text());
}
