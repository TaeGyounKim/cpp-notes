#include <cstdio>
#include <functional>
#include <string>
#include <vector>

// 다중 상속·템플릿·CRTP 믹스인과 MVC는 C++11로 그대로 된다.
// 명시적 객체 매개변수(C++23)만 빠진다.
class Slider {
public:
    Slider() : m_value(0) {}
    void set(int v) { m_value = v; }
    int get() const { return m_value; }

private:
    int m_value;
};

template <typename T>
class WithUndo : public T {
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

template <typename Derived>
class Describable {
public:
    std::string describe() const
    {
        const Derived& self = static_cast<const Derived&>(*this);
        return "<" + self.kind() + ">";
    }
};

class Point : public Describable<Point> {
public:
    std::string kind() const { return "point"; }
};

class Thermostat {
public:
    typedef std::function<void(const Thermostat&)> Listener;
    Thermostat() : m_target(20.0) {}
    void subscribe(Listener l) { m_listeners.push_back(l); }
    void set_target(double t)
    {
        m_target = t;
        for (std::size_t i = 0; i < m_listeners.size(); ++i) {
            m_listeners[i](*this);
        }
    }
    double target() const { return m_target; }

private:
    double m_target;
    std::vector<Listener> m_listeners;
};

void text_view(const Thermostat& m)
{
    std::printf("target %.1f\n", m.target());
}

int main()
{
    WithUndo<Slider> s;
    s.set(10);
    s.set(25);
    s.undo();
    std::printf("slider %d\n", s.get());

    Point p;
    std::printf("%s\n", p.describe().c_str());

    Thermostat model;
    model.subscribe(text_view);
    model.set_target(21.5);
}
