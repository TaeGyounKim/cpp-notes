#include <memory>
#include <print>
#include <string>
#include <vector>

// 템플릿: 모든 타입에 "같은 일"을 한다. 타입은 컴파일할 때 정해진다.
template <typename T>
T largest(const std::vector<T>& values)
{
    T result{ values.front() };
    for (const auto& value : values) {
        if (result < value) {
            result = value;
        }
    }
    return result;
}

// 상속: 관련된 타입마다 "다른 일"을 한다. 타입은 실행할 때 정해진다.
class Discount
{
public:
    virtual ~Discount() = default;
    virtual int apply(int price) const = 0;
};

class PercentOff : public Discount
{
public:
    explicit PercentOff(int percent) : m_percent{ percent } {}
    int apply(int price) const override
    {
        return price * (100 - m_percent) / 100;
    }

private:
    int m_percent;
};

class AmountOff : public Discount
{
public:
    explicit AmountOff(int amount) : m_amount{ amount } {}
    int apply(int price) const override { return price - m_amount; }

private:
    int m_amount;
};

int main()
{
    std::println("{}", largest(std::vector{ 3, 9, 4 }));
    std::println("{}", largest(std::vector<std::string>{ "pear", "apple" }));

    std::vector<std::unique_ptr<Discount>> discounts;
    discounts.push_back(std::make_unique<PercentOff>(10));
    discounts.push_back(std::make_unique<AmountOff>(3000));
    for (const auto& discount : discounts) {
        std::println("20000원 → {}원", discount->apply(20000));
    }
}
