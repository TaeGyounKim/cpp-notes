#include <print>
#include <stdexcept>

class Account
{
public:
    // 잔액에서 amount를 빼고, 뺀 뒤의 잔액을 돌려준다.
    //
    // 매개변수:
    //   amount: 0보다 커야 한다.
    // 예외:
    //   std::invalid_argument: amount가 0 이하일 때
    //   std::runtime_error: 잔액이 모자랄 때. 이때 잔액은 바뀌지 않는다.
    int withdraw(int amount)
    {
        if (amount <= 0) {
            throw std::invalid_argument{ "amount must be positive" };
        }
        if (amount > m_balance) {
            throw std::runtime_error{ "insufficient balance" };
        }
        m_balance -= amount;
        return m_balance;
    }

    int getBalance() const { return m_balance; }

private:
    int m_balance{ 10000 };
};

int main()
{
    Account account;
    std::println("{}", account.withdraw(3000));

    try {
        account.withdraw(50000);
    } catch (const std::runtime_error& exception) {
        std::println("실패: {} (잔액 {})", exception.what(),
                     account.getBalance());
    }
}
