#include <cstddef>
#include <exception>
#include <functional>
#include <memory>
#include <new>
#include <print>
#include <set>
#include <source_location>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// ---------- 아주 작은 테스트 도구 ----------
struct TestCase {
    std::string name;
    std::function<void()> body;
};
std::vector<TestCase>& registry()
{
    static std::vector<TestCase> tests;
    return tests;
}
struct Register {
    Register(std::string name, std::function<void()> body)
    {
        registry().push_back({ std::move(name), std::move(body) });
    }
};
struct CheckFailed : std::runtime_error {
    using std::runtime_error::runtime_error;
};

void check(bool ok, const char* expr,
           std::source_location where = std::source_location::current())
{
    if (!ok) {
        throw CheckFailed{ std::string{ expr } + " (줄 " +
                           std::to_string(where.line()) + ")" };
    }
}
#define CHECK(expr) check(static_cast<bool>(expr), #expr)

template <typename E, typename F>
void check_throws(F f, const char* what)
{
    try { f(); }
    catch (const E&) { return; }      // 기대한 예외: 통과
    catch (...) { throw CheckFailed{ std::string{ what } + ": 다른 예외" }; }
    throw CheckFailed{ std::string{ what } + ": 예외가 나지 않음" };
}

#define TEST(name)                                     \
    void name();                                       \
    Register reg_##name{ #name, name };                \
    void name()

int run_all()
{
    int failed{ 0 };
    for (const auto& t : registry()) {
        try {
            t.body();
            std::println("[통과] {}", t.name);
        } catch (const CheckFailed& e) {
            ++failed;
            std::println("[실패] {}: {}", t.name, e.what());
        } catch (const std::exception& e) {
            ++failed;
            std::println("[오류] {}: 예상 못 한 예외 {}", t.name, e.what());
        }
    }
    std::println("{}개 중 {}개 실패", registry().size(), failed);
    return failed == 0 ? 0 : 1;
}

// ---------- 시험 대상: 29장의 객체 풀 ----------
template <typename T, std::size_t ChunkSize = 4>
class Pool {
public:
    struct Returner {
        Pool* pool;
        void operator()(T* p) const
        {
            std::destroy_at(p);
            pool->m_free.push_back(p);
        }
    };
    using Handle = std::unique_ptr<T, Returner>;

    Pool() = default;
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;
    ~Pool()
    {
        for (T* c : m_chunks) { m_alloc.deallocate(c, ChunkSize); }
    }

    template <typename... Args>
    Handle acquire(Args&&... args)
    {
        if (m_free.empty()) { add_chunk(); }
        T* slot{ m_free.back() };
        T* obj{ ::new (slot) T(std::forward<Args>(args)...) };
        m_free.pop_back();   // 생성자가 던지면 칸은 목록에 그대로 남음
        return Handle{ obj, Returner{ this } };
    }
    std::size_t chunks() const { return m_chunks.size(); }
    std::size_t free_slots() const { return m_free.size(); }

private:
    void add_chunk()
    {
        T* chunk{ m_alloc.allocate(ChunkSize) };
        m_chunks.push_back(chunk);
        for (std::size_t i{ 0 }; i < ChunkSize; ++i) {
            m_free.push_back(chunk + i);
        }
    }
    std::allocator<T> m_alloc;
    std::vector<T*> m_chunks;
    std::vector<T*> m_free;
};

// 시험용 도우미: 살아 있는 개수를 세고, 음수를 받으면 던진다.
struct Probe {
    static inline int alive{ 0 };
    explicit Probe(int v) : value{ v }
    {
        if (v < 0) { throw std::invalid_argument{ "negative" }; }
        ++alive;
    }
    ~Probe() { --alive; }
    int value;
};

// ---------- 테스트 ----------
TEST(acquire_passes_arguments)
{
    // IF 빈 풀이 있을 때
    Pool<Probe> pool;
    // WHEN 인수 7로 객체를 받으면
    auto p{ pool.acquire(7) };
    // THEN 그 값으로 생성되어 있다
    CHECK(p->value == 7);
}

TEST(handles_are_distinct)
{
    Pool<Probe> pool;
    std::set<Probe*> seen;
    std::vector<Pool<Probe>::Handle> held;
    for (int i{ 0 }; i < 10; ++i) {
        held.push_back(pool.acquire(i));
        seen.insert(held.back().get());
    }
    CHECK(seen.size() == 10);   // 동시에 쓰는 객체는 모두 다른 주소
}

TEST(released_slot_is_reused)
{
    Pool<Probe> pool;
    Probe* first{ nullptr };
    {
        auto p{ pool.acquire(1) };
        first = p.get();
    }                            // 여기서 풀로 돌아감
    auto q{ pool.acquire(2) };
    CHECK(q.get() == first);
    CHECK(pool.chunks() == 1);
}

TEST(grows_by_chunk_when_full)
{
    Pool<Probe> pool;            // 덩어리 하나에 4칸
    std::vector<Pool<Probe>::Handle> held;
    for (int i{ 0 }; i < 5; ++i) { held.push_back(pool.acquire(i)); }
    CHECK(pool.chunks() == 2);
    CHECK(pool.free_slots() == 3);
}

TEST(destructor_runs_on_release)
{
    int before{ Probe::alive };
    {
        Pool<Probe> pool;
        auto a{ pool.acquire(1) };
        auto b{ pool.acquire(2) };
        CHECK(Probe::alive == before + 2);
    }
    CHECK(Probe::alive == before);
}

TEST(constructor_exception_propagates)   // 부정 테스트
{
    Pool<Probe> pool;
    check_throws<std::invalid_argument>([&] { pool.acquire(-1); },
                                        "acquire(-1)");
    CHECK(pool.free_slots() == 4);   // 실패해도 칸을 잃지 않음
}

TEST(deliberately_wrong_expectation)   // 실패가 어떻게 보이는지
{
    Pool<Probe> pool;
    auto p{ pool.acquire(3) };
    CHECK(p->value == 4);
}

int main() { return run_all(); }
