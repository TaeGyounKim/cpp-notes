#include <iostream>

class Money
{
public:
    explicit Money(long long won) : m_won{ won } {}
    long long getWon() const { return m_won; }

private:
    long long m_won;
};

Money operator+(const Money& a, const Money& b)
{
    return Money{ a.getWon() + b.getWon() };
}

// std::formatter(C++20) 대신 << 연산자를 만들어 스트림으로 출력한다.
std::ostream& operator<<(std::ostream& out, const Money& money)
{
    return out << money.getWon() << "원";
}

int main()
{
    Money price{ 15000 };
    Money coupon{ 2000 };
    std::cout << price + coupon << '\n';
}
