#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <print>
#include <string>
#include <utility>

// ===== 관찰자: 바뀌면 등록된 쪽에 알린다 =====
template <typename... Args>
class Signal final {
public:
    using Slot = std::function<void(const Args&...)>;

    // 연결 해제를 소멸자가 맡는 RAII 연결 객체
    class Connection {
    public:
        Connection() = default;
        Connection(Signal* s, std::size_t id) : m_signal{ s }, m_id{ id } {}
        Connection(Connection&& o) noexcept
            : m_signal{ std::exchange(o.m_signal, nullptr) }, m_id{ o.m_id } {}
        Connection& operator=(Connection&& o) noexcept
        {
            disconnect();
            m_signal = std::exchange(o.m_signal, nullptr);
            m_id = o.m_id;
            return *this;
        }
        ~Connection() { disconnect(); }
        void disconnect()
        {
            if (m_signal) { m_signal->m_slots.erase(m_id); m_signal = nullptr; }
        }

    private:
        Signal* m_signal{ nullptr };
        std::size_t m_id{ 0 };
    };

    [[nodiscard]] Connection connect(Slot slot)
    {
        m_slots[++m_last] = std::move(slot);
        return Connection{ this, m_last };
    }
    void emit(const Args&... args) const
    {
        for (const auto& [id, slot] : m_slots) { slot(args...); }
    }

private:
    std::map<std::size_t, Slot> m_slots;
    std::size_t m_last{ 0 };
};

class Inventory {                       // 관찰 대상(subject)
public:
    Signal<std::string, int> stock_changed;
    Signal<std::string> sold_out;

    void set(const std::string& item, int qty)
    {
        m_stock[item] = qty;
        stock_changed.emit(item, qty);
        if (qty == 0) { sold_out.emit(item); }
    }

private:
    std::map<std::string, int> m_stock;
};

class Dashboard {                       // 관찰자: 구독을 스스로 관리
public:
    explicit Dashboard(Inventory& inv)
        : m_conn{ inv.stock_changed.connect(
              [this](const std::string& item, const int& qty) {
                  std::println("  [대시보드] {} → {}개", item, qty);
                  ++m_updates;
              }) } {}
    int updates() const { return m_updates; }

private:
    Signal<std::string, int>::Connection m_conn;   // 사라지면 자동 해제
    int m_updates{ 0 };
};

// ===== 책임 연쇄: 처리할 수 있는 첫 처리기가 처리한다 =====
struct Ticket {
    std::string title;
    int severity;                       // 1 가벼움 ... 4 치명적
};

class Handler {
public:
    virtual ~Handler() = default;
    Handler& then(std::unique_ptr<Handler> next)   // 사슬 잇기
    {
        m_next = std::move(next);
        return *m_next;
    }
    void handle(const Ticket& t) const
    {
        if (can_handle(t)) { process(t); }
        else if (m_next) { m_next->handle(t); }    // 다음에게 넘김
        else { std::println("  처리할 곳 없음: {}", t.title); }
    }

private:
    virtual bool can_handle(const Ticket& t) const = 0;
    virtual void process(const Ticket& t) const = 0;
    std::unique_ptr<Handler> m_next;
};

class FaqBot : public Handler {
    bool can_handle(const Ticket& t) const override { return t.severity <= 1; }
    void process(const Ticket& t) const override
    {
        std::println("  자동 답변: {}", t.title);
    }
};
class Agent : public Handler {
    bool can_handle(const Ticket& t) const override { return t.severity <= 2; }
    void process(const Ticket& t) const override
    {
        std::println("  상담원: {}", t.title);
    }
};
class Engineer : public Handler {
    bool can_handle(const Ticket& t) const override { return t.severity <= 3; }
    void process(const Ticket& t) const override
    {
        std::println("  엔지니어: {}", t.title);
    }
};

// ===== 싱글턴: 인스턴스가 하나뿐이고 어디서나 접근 =====
class AppConfig final {
public:
    static AppConfig& instance()
    {
        static AppConfig config;        // 처음 부를 때 한 번, 스레드 안전하게
        return config;
    }
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
    std::string language{ "ko" };

private:
    AppConfig() { std::println("  (설정 객체 생성)"); }
};

int main()
{
    std::println("관찰자");
    Inventory inv;
    auto alert{ inv.sold_out.connect([](const std::string& item) {
        std::println("  [알림] {} 품절!", item);
    }) };
    {
        Dashboard board{ inv };
        inv.set("우유", 3);
        inv.set("우유", 0);
        std::println("  대시보드 갱신 {}번", board.updates());
    }   // board가 사라지며 구독도 해제
    inv.set("빵", 5);                    // 대시보드는 더 이상 받지 않음

    std::println("책임 연쇄");
    FaqBot chain;
    chain.then(std::make_unique<Agent>())
         .then(std::make_unique<Engineer>());
    chain.handle({ "비밀번호 재설정", 1 });
    chain.handle({ "결제 이중 청구", 2 });
    chain.handle({ "서버 응답 느림", 3 });
    chain.handle({ "전체 서비스 중단", 4 });

    std::println("싱글턴");
    AppConfig::instance().language = "en";
    std::println("  언어: {}", AppConfig::instance().language);
    std::println("  같은 객체? {}",
                 &AppConfig::instance() == &AppConfig::instance());
}
