#include <algorithm>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ranges::min_element(C++20) 대신 std::min_element와 비교 람다,
// make_unique(C++14) 대신 unique_ptr에 new를 넘긴다.
class ITransport {
public:
    virtual ~ITransport() {}
    virtual std::string name() const = 0;
};
class Truck : public ITransport {
public:
    std::string name() const override { return "truck"; }
};
class Ship : public ITransport {
public:
    std::string name() const override { return "ship"; }
};

class Logistics {
public:
    Logistics() : m_produced(0) {}
    virtual ~Logistics() {}
    std::unique_ptr<ITransport> request()
    {
        ++m_produced;
        return create();
    }
    int produced() const { return m_produced; }

private:
    virtual std::unique_ptr<ITransport> create() = 0;
    int m_produced;
};

class RoadLogistics final : public Logistics {
    std::unique_ptr<ITransport> create() override
    {
        return std::unique_ptr<ITransport>(new Truck);
    }
};
class SeaLogistics final : public Logistics {
    std::unique_ptr<ITransport> create() override
    {
        return std::unique_ptr<ITransport>(new Ship);
    }
};

typedef std::vector<std::unique_ptr<Logistics> > Factories;

class LeastBusy final : public Logistics {
public:
    explicit LeastBusy(Factories all) : m_all(std::move(all)) {}

private:
    std::unique_ptr<ITransport> create() override
    {
        Factories::iterator it = std::min_element(m_all.begin(), m_all.end(),
            [](const std::unique_ptr<Logistics>& a,
               const std::unique_ptr<Logistics>& b) {
                return a->produced() < b->produced();
            });
        return (*it)->request();
    }
    Factories m_all;
};

int main()
{
    Factories all;
    all.push_back(std::unique_ptr<Logistics>(new RoadLogistics));
    all.push_back(std::unique_ptr<Logistics>(new SeaLogistics));
    all[0]->request();
    all[0]->request();
    LeastBusy dispatcher(std::move(all));
    for (int i = 0; i < 5; ++i) {
        std::printf("%s ", dispatcher.request()->name().c_str());
    }
    std::printf("\n");
}
