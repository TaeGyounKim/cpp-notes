#include <format>
#include <print>
#include <string>

class Money
{
public:
    explicit Money(long long won) : m_won{ won } {}
    long long getWon() const { return m_won; }

    // 멤버 함수로 제공한 인터페이스
    Money add(const Money& other) const { return Money{ m_won + other.m_won }; }

private:
    long long m_won;
};

// 연산자로 제공한 인터페이스: 기본 타입과 같은 모양으로 쓴다.
Money operator+(const Money& a, const Money& b)
{
    return Money{ a.getWon() + b.getWon() };
}

Money operator-(const Money& a, const Money& b)
{
    return Money{ a.getWon() - b.getWon() };
}

bool operator==(const Money& a, const Money& b)
{
    return a.getWon() == b.getWon();
}

// {}로 출력할 수 있게 한다(2장의 formatter 물려받기).
template <>
struct std::formatter<Money> : std::formatter<std::string>
{
    auto format(const Money& money, auto& context) const
    {
        return std::formatter<std::string>::format(
            std::format("{}원", money.getWon()), context);
    }
};

int main()
{
    Money price{ 15'000 };
    Money coupon{ 2'000 };

    // 멤버 함수 방식
    Money total1{ price.add(coupon) };

    // 연산자 방식: 숫자를 다루듯 읽힌다.
    Money total2{ price + coupon };
    Money paid{ price - coupon };

    std::println("{} {} {}", total1, total2, paid);
    std::println("같은가: {}", total1 == total2);
}
