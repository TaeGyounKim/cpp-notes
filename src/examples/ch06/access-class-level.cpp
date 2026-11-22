#include <print>
#include <string>
#include <utility>

class Money
{
public:
    Money(long long amount, std::string currency)
        : m_amount{ amount }, m_currency{ std::move(currency) }
    {
    }

    // 다른 Money 객체의 private 멤버에도 접근할 수 있다.
    // 접근 제어는 객체 단위가 아니라 클래스 단위이기 때문이다.
    bool hasSameCurrency(const Money& other) const
    {
        return m_currency == other.m_currency;
    }

    long long getAmount() const { return m_amount; }

private:
    long long m_amount;
    std::string m_currency;
};

int main()
{
    Money price{ 15'000, "KRW" };
    Money tip{ 3, "USD" };
    std::println("같은 통화인가: {}", price.hasSameCurrency(tip));
    // std::println("{}", price.m_currency);   // 컴파일 오류: private
}
