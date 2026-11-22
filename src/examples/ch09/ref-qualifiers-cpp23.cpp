#include <print>
#include <string>
#include <utility>

class Label
{
public:
    explicit Label(std::string text) : m_text{ std::move(text) } {}

    // C++23: 명시적 객체 매개변수로 쓴 참조 한정. 어디에 붙는지 잘 보인다.
    const std::string& text(this const Label& self) { return self.m_text; }
    std::string&& text(this Label&& self) { return std::move(self.m_text); }

    Label& operator=(this Label& self, const std::string& rhs)
    {
        self.m_text = rhs;
        return self;
    }

private:
    std::string m_text;
};

int main()
{
    Label kitchen{ "부엌" };
    kitchen = "주방";
    std::println("{} / {}", kitchen.text(), Label{ "거실" }.text());
}
