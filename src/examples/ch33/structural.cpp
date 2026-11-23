#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iterator>
#include <memory>
#include <print>
#include <string>
#include <vector>

// ===== 어댑터: 바꿀 수 없는 옛 인터페이스를 원하는 인터페이스로 =====
class LegacyThermometer {               // 외부 라이브러리라 고칠 수 없다고 가정
public:
    int read_fahrenheit_x10(int channel) const   // 화씨의 10배, 채널 번호
    {
        return channel == 0 ? 986 : 320;
    }
};

class ITemperature {                     // 우리 코드가 원하는 인터페이스
public:
    virtual ~ITemperature() = default;
    virtual double celsius() const = 0;
};

class ThermometerAdapter : public ITemperature {
public:
    ThermometerAdapter(const LegacyThermometer& t, int channel)
        : m_device{ t }, m_channel{ channel } {}
    double celsius() const override
    {
        double f{ m_device.read_fahrenheit_x10(m_channel) / 10.0 };
        return (f - 32.0) * 5.0 / 9.0;  // 단위와 호출 방식을 맞춤
    }

private:
    const LegacyThermometer& m_device;
    int m_channel;
};

// ===== 프록시: 진짜 객체 대신 서서 필요할 때만 일을 넘긴다 =====
class IImage {
public:
    virtual ~IImage() = default;
    virtual std::string draw() const = 0;
    virtual std::string name() const = 0;
};

class DiskImage : public IImage {        // 만들 때 비용이 큼
public:
    explicit DiskImage(std::string file) : m_file{ std::move(file) }
    {
        std::println("    (디스크에서 {} 읽음)", m_file);
    }
    std::string draw() const override { return "그림:" + m_file; }
    std::string name() const override { return m_file; }

private:
    std::string m_file;
};

class LazyImage : public IImage {        // 가상 프록시: 처음 그릴 때 읽음
public:
    explicit LazyImage(std::string file) : m_file{ std::move(file) } {}
    std::string draw() const override
    {
        if (!m_real) { m_real = std::make_unique<DiskImage>(m_file); }
        return m_real->draw();
    }
    std::string name() const override { return m_file; }   // 읽지 않고 답함

private:
    std::string m_file;
    mutable std::unique_ptr<DiskImage> m_real;
};

// ===== 데코레이터: 실행 중에 감싸서 기능을 덧붙이고, 겹쳐 쓴다 =====
class IText {
public:
    virtual ~IText() = default;
    virtual std::string render() const = 0;
};

class Plain : public IText {
public:
    explicit Plain(std::string s) : m_s{ std::move(s) } {}
    std::string render() const override { return m_s; }

private:
    std::string m_s;
};

class Decorator : public IText {         // 감싼 대상을 소유
public:
    explicit Decorator(std::unique_ptr<IText> inner)
        : m_inner{ std::move(inner) } {}

protected:
    std::string inner() const { return m_inner->render(); }

private:
    std::unique_ptr<IText> m_inner;
};

class Upper : public Decorator {
public:
    using Decorator::Decorator;
    std::string render() const override
    {
        std::string s{ inner() };
        for (char& c : s) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return s;
    }
};

class Exclaim : public Decorator {
public:
    using Decorator::Decorator;
    std::string render() const override { return inner() + "!"; }
};

class Quote : public Decorator {
public:
    using Decorator::Decorator;
    std::string render() const override { return "\"" + inner() + "\""; }
};

// ===== 반복자: 구조를 몰라도 알고리즘이 돌 수 있게 =====
class Countdown {                        // 저장 없이 n, n-1, ..., 1을 내놓음
public:
    class iterator {
    public:
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        iterator() = default;
        explicit iterator(int v) : m_v{ v } {}
        int operator*() const { return m_v; }
        iterator& operator++() { --m_v; return *this; }
        iterator operator++(int) { auto t{ *this }; --m_v; return t; }
        bool operator==(const iterator&) const = default;

    private:
        int m_v{ 0 };
    };
    explicit Countdown(int n) : m_n{ n } {}
    iterator begin() const { return iterator{ m_n }; }
    iterator end() const { return iterator{ 0 }; }

private:
    int m_n;
};

int main()
{
    std::println("어댑터");
    LegacyThermometer legacy;
    std::vector<std::unique_ptr<ITemperature>> sensors;
    sensors.push_back(std::make_unique<ThermometerAdapter>(legacy, 0));
    sensors.push_back(std::make_unique<ThermometerAdapter>(legacy, 1));
    for (const auto& s : sensors) { std::println("  {:.1f}도", s->celsius()); }

    std::println("프록시");
    std::vector<std::unique_ptr<IImage>> doc;
    doc.push_back(std::make_unique<LazyImage>("cover.png"));
    doc.push_back(std::make_unique<LazyImage>("chart.png"));
    std::println("  문서 열기 완료: {}, {}", doc[0]->name(), doc[1]->name());
    std::println("  {}", doc[1]->draw());   // 이때 처음 읽음
    std::println("  {}", doc[1]->draw());   // 다시 읽지 않음

    std::println("데코레이터");
    std::unique_ptr<IText> t{ std::make_unique<Plain>("hello") };
    t = std::make_unique<Exclaim>(std::move(t));
    t = std::make_unique<Upper>(std::move(t));
    t = std::make_unique<Quote>(std::move(t));
    std::println("  {}", t->render());

    std::println("반복자");
    Countdown c{ 5 };
    for (int v : c) { std::print("  {}", v); }
    std::println("");
    auto even{ std::ranges::count_if(c, [](int v) { return v % 2 == 0; }) };
    std::println("  짝수 {}개", even);   // 표준 알고리즘이 그대로 동작
}
