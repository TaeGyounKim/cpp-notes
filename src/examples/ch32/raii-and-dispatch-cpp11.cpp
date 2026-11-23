#include <cstdio>
#include <memory>
#include <vector>

// std::exchange(C++14) 대신 직접 옮기고 비우며,
// [[nodiscard]](C++17, 생성자에는 C++20)는 쓰지 않는다.
int g_open = 0;
int open_channel() { return ++g_open; }
void close_channel(int id)
{
    std::printf("close #%d\n", id);
    --g_open;
}

class Channel final {
public:
    Channel() : m_id(open_channel()) {}
    ~Channel() { if (m_id != 0) { close_channel(m_id); } }
    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;
    Channel(Channel&& src) noexcept : m_id(src.m_id) { src.m_id = 0; }

private:
    int m_id;
};

class Rock;
class Paper;
class Scissors;

class Hand {
public:
    virtual ~Hand() {}
    virtual const char* name() const = 0;
    virtual bool beats(const Hand& other) const = 0;
    virtual bool beaten_by(const Rock&) const = 0;
    virtual bool beaten_by(const Paper&) const = 0;
    virtual bool beaten_by(const Scissors&) const = 0;
};

class Rock : public Hand {
public:
    const char* name() const override { return "rock"; }
    bool beats(const Hand& o) const override { return o.beaten_by(*this); }
    bool beaten_by(const Rock&) const override { return false; }
    bool beaten_by(const Paper&) const override { return true; }
    bool beaten_by(const Scissors&) const override { return false; }
};

class Paper : public Hand {
public:
    const char* name() const override { return "paper"; }
    bool beats(const Hand& o) const override { return o.beaten_by(*this); }
    bool beaten_by(const Rock&) const override { return false; }
    bool beaten_by(const Paper&) const override { return false; }
    bool beaten_by(const Scissors&) const override { return true; }
};

class Scissors : public Hand {
public:
    const char* name() const override { return "scissors"; }
    bool beats(const Hand& o) const override { return o.beaten_by(*this); }
    bool beaten_by(const Rock&) const override { return true; }
    bool beaten_by(const Paper&) const override { return false; }
    bool beaten_by(const Scissors&) const override { return false; }
};

int main()
{
    {
        Channel a;
        Channel b(std::move(a));
        std::printf("open %d\n", g_open);
    }
    std::printf("open %d\n", g_open);

    std::vector<std::unique_ptr<Hand> > hands;
    hands.push_back(std::unique_ptr<Hand>(new Rock));
    hands.push_back(std::unique_ptr<Hand>(new Paper));
    hands.push_back(std::unique_ptr<Hand>(new Scissors));
    for (std::size_t i = 0; i < hands.size(); ++i) {
        for (std::size_t j = 0; j < hands.size(); ++j) {
            if (hands[i]->beats(*hands[j])) {
                std::printf("%s beats %s\n", hands[i]->name(),
                            hands[j]->name());
            }
        }
    }
}
