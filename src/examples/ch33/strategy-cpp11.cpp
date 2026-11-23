#include <cstdio>
#include <functional>
#include <memory>

// 전략 패턴은 C++11로 그대로 쓸 수 있다. 출력만 printf로.
class IShippingCost {
public:
    virtual ~IShippingCost() {}
    virtual double cost(double weight_kg) const = 0;
};

class FlatRate : public IShippingCost {
public:
    double cost(double) const override { return 3000; }
};

class ByWeight : public IShippingCost {
public:
    explicit ByWeight(double per_kg) : m_per_kg(per_kg) {}
    double cost(double w) const override { return 1000 + w * m_per_kg; }

private:
    double m_per_kg;
};

class Checkout {
public:
    explicit Checkout(std::shared_ptr<IShippingCost> s) : m_shipping(s) {}
    void set_shipping(std::shared_ptr<IShippingCost> s) { m_shipping = s; }
    double total(double items, double w) const
    {
        return items + m_shipping->cost(w);
    }

private:
    std::shared_ptr<IShippingCost> m_shipping;
};

int main()
{
    Checkout checkout(std::make_shared<FlatRate>());
    std::printf("%.0f\n", checkout.total(20000, 4));
    checkout.set_shipping(std::make_shared<ByWeight>(700));
    std::printf("%.0f\n", checkout.total(20000, 4));

    std::function<double(double)> free_over =
        [](double w) { return w > 10 ? 0.0 : 2500.0; };
    std::printf("%.0f\n", 20000 + free_over(12));
}
