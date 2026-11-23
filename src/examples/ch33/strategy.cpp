#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

// 전략 인터페이스: 운임을 어떻게 계산할지
class IShippingCost {
public:
    virtual ~IShippingCost() = default;
    virtual double cost(double weight_kg) const = 0;
    virtual std::string name() const = 0;
};

class FlatRate : public IShippingCost {
public:
    double cost(double) const override { return 3000; }
    std::string name() const override { return "정액"; }
};

class ByWeight : public IShippingCost {
public:
    explicit ByWeight(double per_kg) : m_per_kg{ per_kg } {}
    double cost(double w) const override { return 1000 + w * m_per_kg; }
    std::string name() const override { return "무게별"; }

private:
    double m_per_kg;
};

// 전략을 쓰는 쪽: 구체 클래스를 모르고 인터페이스만 앎(의존성 역전)
class Checkout {
public:
    explicit Checkout(std::shared_ptr<IShippingCost> shipping)   // 주입
        : m_shipping{ std::move(shipping) } {}
    void set_shipping(std::shared_ptr<IShippingCost> s)          // 바꿔 끼우기
    {
        m_shipping = std::move(s);
    }
    double total(double items, double weight) const
    {
        return items + m_shipping->cost(weight);
    }
    std::string shipping_name() const { return m_shipping->name(); }

private:
    std::shared_ptr<IShippingCost> m_shipping;
};

// 테스트용 목(mock): 불린 횟수와 인수를 기록
class MockShipping : public IShippingCost {
public:
    double cost(double w) const override
    {
        ++calls;
        last_weight = w;
        return 100;
    }
    std::string name() const override { return "목"; }
    mutable int calls{ 0 };
    mutable double last_weight{ 0 };
};

// 가벼운 대안: 전략을 std::function으로
class LightCheckout {
public:
    using Strategy = std::function<double(double)>;
    explicit LightCheckout(Strategy s) : m_cost{ std::move(s) } {}
    double total(double items, double w) const { return items + m_cost(w); }

private:
    Strategy m_cost;
};

int main()
{
    Checkout checkout{ std::make_shared<FlatRate>() };
    std::println("{}: {}원", checkout.shipping_name(),
                 checkout.total(20000, 4));
    checkout.set_shipping(std::make_shared<ByWeight>(700));   // 실행 중 교체
    std::println("{}: {}원", checkout.shipping_name(),
                 checkout.total(20000, 4));

    auto mock{ std::make_shared<MockShipping>() };
    Checkout under_test{ mock };
    double t{ under_test.total(5000, 2.5) };
    std::println("목 주입 테스트: 합계 {}, 호출 {}번, 무게 {}",
                 t, mock->calls, mock->last_weight);

    LightCheckout free_over{ [](double w) { return w > 10 ? 0.0 : 2500.0; } };
    std::println("람다 전략: {}원", free_over.total(20000, 12));
}
