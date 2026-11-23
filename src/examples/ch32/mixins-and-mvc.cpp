#include <format>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

// ===== 1) 다중 상속 믹스인: 주 계층과 다른 축의 기능 =====
class Document {                       // 주 계층
public:
    virtual ~Document() = default;
    virtual std::string title() const = 0;
};

class Exportable {                     // 믹스인: "내보낼 수 있다"
public:
    virtual ~Exportable() = default;
    void export_to(const std::string& format) const
    {
        std::println("  [{}] {} 내보냄", format, export_name());
    }

private:
    virtual std::string export_name() const = 0;
};

class Note : public Document {          // 내보내기 없음
public:
    std::string title() const override { return "메모"; }
};

class Report : public Document, public Exportable {   // 섞어 넣음
public:
    std::string title() const override { return "보고서"; }

private:
    std::string export_name() const override { return title(); }
};

// ===== 2) 클래스 템플릿 믹스인: 기존 클래스를 고치지 않고 기능을 덧입힘 =====
class Slider {
public:
    void set(int v) { m_value = v; }
    int get() const { return m_value; }

private:
    int m_value{ 0 };
};

template <typename T>
class WithUndo : public T {             // T에서 파생해 set을 감쌈
public:
    void set(int v)
    {
        m_history.push_back(this->get());
        T::set(v);
    }
    void undo()
    {
        if (m_history.empty()) { return; }
        T::set(m_history.back());
        m_history.pop_back();
    }

private:
    std::vector<int> m_history;
};

// ===== 3) CRTP 믹스인: 파생 타입을 템플릿 인수로 받음 =====
template <typename Derived>
class Describable {
public:
    std::string describe() const
    {
        const auto& self{ static_cast<const Derived&>(*this) };
        return std::format("<{}: {}>", self.kind(), self.summary());
    }
};

class Point : public Describable<Point> {
public:
    std::string kind() const { return "점"; }
    std::string summary() const { return "(1, 2)"; }
};

// ===== 4) 명시적 객체 매개변수(C++23)로 쓴 CRTP 없는 믹스인 =====
class Describable23 {
public:
    std::string describe(this const auto& self)   // self의 타입이 파생 타입
    {
        return std::format("<{}: {}>", self.kind(), self.summary());
    }
};

class Circle : public Describable23 {
public:
    std::string kind() const { return "원"; }
    std::string summary() const { return "r=3"; }
};

// ===== 5) MVC: 모델, 뷰 둘, 컨트롤러 =====
class Thermostat {                      // 모델: 데이터와 변경 알림
public:
    using Listener = std::function<void(const Thermostat&)>;
    void subscribe(Listener l) { m_listeners.push_back(std::move(l)); }
    void set_target(double t)
    {
        m_target = t;
        for (const auto& l : m_listeners) { l(*this); }   // 뷰에 알림
    }
    double target() const { return m_target; }

private:
    double m_target{ 20.0 };
    std::vector<Listener> m_listeners;
};

void text_view(const Thermostat& m)     // 뷰 1: 숫자
{
    std::println("  텍스트 뷰: 목표 {:.1f}도", m.target());
}

void bar_view(const Thermostat& m)      // 뷰 2: 막대
{
    int bars{ static_cast<int>(m.target()) - 15 };
    std::println("  막대 뷰:   {}", std::string(bars, '#'));
}

class Controller {                      // 컨트롤러: 사건을 모델 변경으로
public:
    explicit Controller(Thermostat& m) : m_model{ m } {}
    void on_key(char key)
    {
        if (key == '+') { m_model.set_target(m_model.target() + 0.5); }
        if (key == '-') { m_model.set_target(m_model.target() - 0.5); }
    }

private:
    Thermostat& m_model;
};

int main()
{
    std::println("1) 다중 상속 믹스인");
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<Note>());
    docs.push_back(std::make_unique<Report>());
    for (const auto& d : docs) {
        if (auto* e{ dynamic_cast<const Exportable*>(d.get()) }) {
            e->export_to("PDF");
        } else {
            std::println("  {}: 내보낼 수 없음", d->title());
        }
    }

    std::println("2) 템플릿 믹스인");
    WithUndo<Slider> s;
    s.set(10);
    s.set(25);
    s.undo();
    std::println("  되돌린 뒤 값 {}", s.get());

    std::println("3) CRTP, 4) 명시적 객체 매개변수");
    std::println("  {} {}", Point{}.describe(), Circle{}.describe());

    std::println("5) MVC");
    Thermostat model;
    model.subscribe(text_view);
    model.subscribe(bar_view);
    Controller controller{ model };
    for (char key : std::string{ "++-" }) { controller.on_key(key); }
}
