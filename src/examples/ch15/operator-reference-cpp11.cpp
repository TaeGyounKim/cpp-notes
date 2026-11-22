#include <iostream>
#include <string>
#include <utility>

// <=>와 기본 비교(C++20)가 없으므로 ==와 <를 직접 쓰고 나머지를 만든다.
// std::rel_ops는 C++20에서 권장하지 않게 되었으므로 쓰지 않는다.
class Label
{
public:
    explicit Label(std::string text) : m_text(std::move(text)) {}
    const std::string& text() const { return m_text; }

private:
    std::string m_text;
};

bool operator==(const Label& a, const Label& b) { return a.text() == b.text(); }
bool operator<(const Label& a, const Label& b) { return a.text() < b.text(); }
bool operator!=(const Label& a, const Label& b) { return !(a == b); }
bool operator>(const Label& a, const Label& b) { return b < a; }
bool operator<=(const Label& a, const Label& b) { return !(b < a); }
bool operator>=(const Label& a, const Label& b) { return !(a < b); }

int main()
{
    Label a("온도");
    Label b("센서");
    std::cout << std::boolalpha << (a < b) << ' ' << (a != b) << ' '
              << (a >= a) << ' ' << ((a == a) and not (a == b)) << '\n';
}
