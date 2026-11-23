#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// ===== 추상 팩토리: 서로 어울리는 제품 "묶음"을 만든다 =====
class IButton {
public:
    virtual ~IButton() = default;
    virtual std::string render() const = 0;
};
class ICheckbox {
public:
    virtual ~ICheckbox() = default;
    virtual std::string render() const = 0;
};

class LightButton : public IButton {
public:
    std::string render() const override { return "[ 확인 ] (밝은)"; }
};
class LightCheckbox : public ICheckbox {
public:
    std::string render() const override { return "[v] (밝은)"; }
};
class DarkButton : public IButton {
public:
    std::string render() const override { return "[ 확인 ] (어두운)"; }
};
class DarkCheckbox : public ICheckbox {
public:
    std::string render() const override { return "[v] (어두운)"; }
};

class IWidgetFactory {                  // 추상 팩토리
public:
    virtual ~IWidgetFactory() = default;
    virtual std::unique_ptr<IButton> make_button() const = 0;
    virtual std::unique_ptr<ICheckbox> make_checkbox() const = 0;
};
class LightTheme : public IWidgetFactory {
public:
    std::unique_ptr<IButton> make_button() const override
    {
        return std::make_unique<LightButton>();
    }
    std::unique_ptr<ICheckbox> make_checkbox() const override
    {
        return std::make_unique<LightCheckbox>();
    }
};
class DarkTheme : public IWidgetFactory {
public:
    std::unique_ptr<IButton> make_button() const override
    {
        return std::make_unique<DarkButton>();
    }
    std::unique_ptr<ICheckbox> make_checkbox() const override
    {
        return std::make_unique<DarkCheckbox>();
    }
};

void build_dialog(const IWidgetFactory& f)   // 구체 테마를 모름
{
    std::println("  {}  {}", f.make_button()->render(),
                 f.make_checkbox()->render());
}

// ===== 팩토리 메서드: 무엇을 만들지는 파생 팩토리가 정한다 =====
class ITransport {
public:
    virtual ~ITransport() = default;
    virtual std::string name() const = 0;
};
class Truck : public ITransport {
public:
    std::string name() const override { return "트럭"; }
};
class Ship : public ITransport {
public:
    std::string name() const override { return "배"; }
};

class Logistics {
public:
    virtual ~Logistics() = default;
    std::unique_ptr<ITransport> request()   // 비가상 공개 인터페이스(NVI)
    {
        ++m_produced;
        return create();
    }
    int produced() const { return m_produced; }

private:
    virtual std::unique_ptr<ITransport> create() = 0;   // 팩토리 메서드
    int m_produced{ 0 };
};

class RoadLogistics final : public Logistics {
    std::unique_ptr<ITransport> create() override
    {
        return std::make_unique<Truck>();
    }
};
class SeaLogistics final : public Logistics {
    std::unique_ptr<ITransport> create() override
    {
        return std::make_unique<Ship>();
    }
};

// 다른 팩토리들 중 가장 한가한 곳에 맡기는 팩토리
class LeastBusy final : public Logistics {
public:
    explicit LeastBusy(std::vector<std::unique_ptr<Logistics>> all)
        : m_all{ std::move(all) } {}

private:
    std::unique_ptr<ITransport> create() override
    {
        auto it{ std::ranges::min_element(m_all, {}, &Logistics::produced) };
        return (*it)->request();
    }
    std::vector<std::unique_ptr<Logistics>> m_all;
};

// ===== 팩토리 함수: 이름표로 만들 타입을 고른다 =====
std::unique_ptr<ITransport> make_transport(const std::string& kind)
{
    static const std::map<std::string,
        std::function<std::unique_ptr<ITransport>()>> registry{
        { "truck", [] { return std::make_unique<Truck>(); } },
        { "ship",  [] { return std::make_unique<Ship>(); } },
    };
    auto it{ registry.find(kind) };
    if (it == registry.end()) { throw std::invalid_argument{ kind }; }
    return it->second();
}

int main()
{
    std::println("추상 팩토리");
    build_dialog(LightTheme{});
    build_dialog(DarkTheme{});

    std::println("팩토리 메서드");
    std::vector<std::unique_ptr<Logistics>> all;
    all.push_back(std::make_unique<RoadLogistics>());
    all.push_back(std::make_unique<SeaLogistics>());
    all[0]->request();
    all[0]->request();   // 도로 쪽이 이미 2대 바쁨
    LeastBusy dispatcher{ std::move(all) };
    std::string order;
    for (int i{ 0 }; i < 5; ++i) {
        order += dispatcher.request()->name() + " ";
    }
    std::println("  {}", order);

    std::println("팩토리 함수");
    std::println("  {}", make_transport("ship")->name());
    try {
        make_transport("plane");
    } catch (const std::invalid_argument& e) {
        std::println("  모르는 종류: {}", e.what());
    }
}
