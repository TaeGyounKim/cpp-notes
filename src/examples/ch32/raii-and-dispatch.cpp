#include <memory>
#include <print>
#include <string>
#include <utility>
#include <variant>
#include <vector>

// ---------- RAII ----------
// C 스타일 자원 API를 흉내 낸 것(열면 번호를 주고, 꼭 닫아야 함)
int g_open{ 0 };
int open_channel(const char* name)
{
    std::println("  열기: {}", name);
    ++g_open;
    return g_open;
}
void close_channel(int id)
{
    std::println("  닫기: #{}", id);
    --g_open;
}

class Channel final {
public:
    [[nodiscard]] explicit Channel(const char* name)
        : m_id{ open_channel(name) } {}
    ~Channel() { reset(); }

    Channel(const Channel&) = delete;              // 자원은 하나뿐
    Channel& operator=(const Channel&) = delete;
    Channel(Channel&& src) noexcept : m_id{ std::exchange(src.m_id, 0) } {}
    Channel& operator=(Channel&& rhs) noexcept
    {
        if (this != &rhs) { reset(); m_id = std::exchange(rhs.m_id, 0); }
        return *this;
    }

    int get() const noexcept { return m_id; }
    void reset() noexcept
    {
        if (m_id != 0) { close_channel(m_id); m_id = 0; }
    }

private:
    int m_id{ 0 };
};

// ---------- 이중 디스패치: 가위바위보 ----------
class Rock;
class Paper;
class Scissors;

class Hand {
public:
    virtual ~Hand() = default;
    virtual std::string name() const = 0;
    virtual bool beats(const Hand& other) const = 0;   // 1차 디스패치
    // "나는 이 손에 지는가?" 2차 디스패치용 오버로드
    virtual bool beaten_by(const Rock&) const = 0;
    virtual bool beaten_by(const Paper&) const = 0;
    virtual bool beaten_by(const Scissors&) const = 0;
};

class Rock : public Hand {
public:
    std::string name() const override { return "바위"; }
    bool beats(const Hand& other) const override
    {
        return other.beaten_by(*this);   // *this의 타입은 Rock으로 고정
    }
    bool beaten_by(const Rock&) const override { return false; }
    bool beaten_by(const Paper&) const override { return true; }
    bool beaten_by(const Scissors&) const override { return false; }
};

class Paper : public Hand {
public:
    std::string name() const override { return "보"; }
    bool beats(const Hand& other) const override
    {
        return other.beaten_by(*this);
    }
    bool beaten_by(const Rock&) const override { return false; }
    bool beaten_by(const Paper&) const override { return false; }
    bool beaten_by(const Scissors&) const override { return true; }
};

class Scissors : public Hand {
public:
    std::string name() const override { return "가위"; }
    bool beats(const Hand& other) const override
    {
        return other.beaten_by(*this);
    }
    bool beaten_by(const Rock&) const override { return true; }
    bool beaten_by(const Paper&) const override { return false; }
    bool beaten_by(const Scissors&) const override { return false; }
};

// ---------- 다른 길: variant + visit(C++17) ----------
struct R {};
struct P {};
struct S {};
using Throw = std::variant<R, P, S>;

struct Beats {   // 두 대안의 모든 조합을 오버로드로
    bool operator()(R, S) const { return true; }
    bool operator()(P, R) const { return true; }
    bool operator()(S, P) const { return true; }
    template <typename A, typename B>
    bool operator()(A, B) const { return false; }
};

int main()
{
    std::println("RAII:");
    {
        Channel log{ "log" };
        Channel data{ "data" };
        Channel moved{ std::move(data) };   // 소유권 이동
        std::println("  열린 채널 {}개", g_open);
    }   // 역순으로 자동으로 닫힘
    std::println("  블록을 나온 뒤 열린 채널 {}개", g_open);

    std::println("이중 디스패치:");
    std::vector<std::unique_ptr<Hand>> hands;
    hands.push_back(std::make_unique<Rock>());
    hands.push_back(std::make_unique<Paper>());
    hands.push_back(std::make_unique<Scissors>());
    for (const auto& a : hands) {
        for (const auto& b : hands) {   // 둘 다 Hand&로만 앎
            if (a->beats(*b)) {
                std::println("  {}는 {}를 이김", a->name(), b->name());
            }
        }
    }

    std::println("variant + visit:");
    std::vector<Throw> throws{ R{}, P{}, S{} };
    int wins{ 0 };
    for (const auto& a : throws) {
        for (const auto& b : throws) {
            if (std::visit(Beats{}, a, b)) { ++wins; }
        }
    }
    std::println("  이기는 조합 {}개", wins);
}
