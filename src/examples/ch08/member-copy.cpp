#include <print>

class Unit
{
public:
    Unit() { std::println("    Unit 기본 생성자"); }
    Unit(const Unit&) { std::println("    Unit 복사 생성자"); }
    Unit& operator=(const Unit&)
    {
        std::println("    Unit 대입 연산자");
        return *this;
    }
};

class InBody
{
public:
    InBody() = default;
    InBody(const InBody& src)
    {
        m_unit = src.m_unit;   // 본문: 이미 만들어진 멤버에 대입
    }

private:
    Unit m_unit;
};

class InList
{
public:
    InList() = default;
    InList(const InList& src) : m_unit{ src.m_unit } {}   // 만들며 복사

private:
    Unit m_unit;
};

int main()
{
    InBody a;
    InList b;

    std::println("본문에서 대입하는 복사 생성자");
    InBody a2{ a };

    std::println("초기화 목록을 쓰는 복사 생성자");
    InList b2{ b };
}
