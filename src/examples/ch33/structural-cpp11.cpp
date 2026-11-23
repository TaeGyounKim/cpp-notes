#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iterator>
#include <memory>
#include <string>

// make_unique(C++14) 대신 new, 기본 비교 연산자(C++20) 대신 직접 정의,
// ranges::count_if(C++20) 대신 std::count_if
class IText {
public:
    virtual ~IText() {}
    virtual std::string render() const = 0;
};

class Plain : public IText {
public:
    explicit Plain(const std::string& s) : m_s(s) {}
    std::string render() const override { return m_s; }

private:
    std::string m_s;
};

class Decorator : public IText {
public:
    explicit Decorator(std::unique_ptr<IText> inner)
        : m_inner(std::move(inner)) {}

protected:
    std::string inner() const { return m_inner->render(); }

private:
    std::unique_ptr<IText> m_inner;
};

class Exclaim : public Decorator {
public:
    using Decorator::Decorator;   // 생성자 상속은 C++11
    std::string render() const override { return inner() + "!"; }
};

class Quote : public Decorator {
public:
    using Decorator::Decorator;
    std::string render() const override { return "\"" + inner() + "\""; }
};

class Countdown {
public:
    class iterator : public std::iterator<std::forward_iterator_tag, int> {
    public:
        explicit iterator(int v = 0) : m_v(v) {}
        int operator*() const { return m_v; }
        iterator& operator++() { --m_v; return *this; }
        bool operator==(const iterator& o) const { return m_v == o.m_v; }
        bool operator!=(const iterator& o) const { return m_v != o.m_v; }

    private:
        int m_v;
    };
    explicit Countdown(int n) : m_n(n) {}
    iterator begin() const { return iterator(m_n); }
    iterator end() const { return iterator(0); }

private:
    int m_n;
};

bool is_even(int v) { return v % 2 == 0; }

int main()
{
    std::unique_ptr<IText> t(new Plain("hello"));
    t.reset(new Exclaim(std::move(t)));
    t.reset(new Quote(std::move(t)));
    std::printf("%s\n", t->render().c_str());

    Countdown c(5);
    for (int v : c) { std::printf("%d ", v); }
    std::printf("\neven %d\n",
                static_cast<int>(std::count_if(c.begin(), c.end(), is_even)));
}
