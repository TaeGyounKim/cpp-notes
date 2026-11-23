#include <array>
#include <chrono>
#include <cstddef>
#include <map>
#include <memory>
#include <new>
#include <print>
#include <string>
#include <utility>
#include <vector>

// ---- 캐시: 느린 원본(파일이라고 가정)을 한 번만 읽는다 ----
class SlowSource {
public:
    int load(const std::string& key) const
    {
        ++m_loads;
        return static_cast<int>(key.size()) * 10;
    }
    void edit() { ++m_version; }              // 원본이 바뀜
    int version() const { return m_version; }
    int loads() const { return m_loads; }

private:
    mutable int m_loads{ 0 };
    int m_version{ 0 };
};

class Prices {   // 바깥에서는 캐시가 있는지 모른다
public:
    explicit Prices(const SlowSource& src) : m_src{ src } {}
    int get(const std::string& key) const
    {
        if (m_seenVersion != m_src.version()) {   // 무효화
            m_cache.clear();
            m_seenVersion = m_src.version();
        }
        auto it{ m_cache.find(key) };
        if (it == m_cache.end()) {
            it = m_cache.emplace(key, m_src.load(key)).first;
        }
        return it->second;
    }

private:
    const SlowSource& m_src;
    mutable std::map<std::string, int> m_cache;
    mutable int m_seenVersion{ 0 };
};

// ---- 객체 풀: 큰 덩어리를 한 번에 받아 칸을 돌려 쓴다 ----
template <typename T, std::size_t ChunkSize = 8>
class Pool {
public:
    struct Returner {
        Pool* pool;
        void operator()(T* p) const
        {
            std::destroy_at(p);           // 소멸자만 부르고
            pool->m_free.push_back(p);    // 메모리는 돌려놓음
        }
    };
    using Handle = std::unique_ptr<T, Returner>;

    Pool() = default;
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;
    ~Pool()
    {
        for (T* chunk : m_chunks) { m_alloc.deallocate(chunk, ChunkSize); }
    }

    template <typename... Args>
    Handle acquire(Args&&... args)
    {
        if (m_free.empty()) { add_chunk(); }
        T* slot{ m_free.back() };
        T* obj{ ::new (slot) T(std::forward<Args>(args)...) };
        m_free.pop_back();
        return Handle{ obj, Returner{ this } };
    }
    std::size_t chunks() const { return m_chunks.size(); }

private:
    void add_chunk()
    {
        T* chunk{ m_alloc.allocate(ChunkSize) };   // 생성자는 아직 안 부름
        m_chunks.push_back(chunk);
        for (std::size_t i{ 0 }; i < ChunkSize; ++i) {
            m_free.push_back(chunk + i);
        }
    }

    std::allocator<T> m_alloc;
    std::vector<T*> m_chunks;
    std::vector<T*> m_free;
};

struct Frame {                      // 짧게 쓰고 버리는 큰 객체
    explicit Frame(int id) : id{ id } {}
    int id;
    std::array<double, 64 * 1024> samples;   // 512KB, 초기화하지 않음
};

int main()
{
    SlowSource source;
    Prices prices{ source };
    int sum{ 0 };
    for (int round{ 0 }; round < 3; ++round) {
        sum += prices.get("apple") + prices.get("kiwi");
    }
    std::println("6번 조회, 원본 읽기 {}번", source.loads());
    source.edit();
    sum += prices.get("apple");
    std::println("원본이 바뀐 뒤 1번 조회, 원본 읽기 {}번 (합 {})",
                 source.loads(), sum);

    constexpr int rounds{ 20'000 };
    using clock = std::chrono::steady_clock;
    long long check{ 0 };

    Pool<Frame> pool;
    auto t0{ clock::now() };
    for (int i{ 0 }; i < rounds; ++i) {
        auto f{ pool.acquire(i) };   // 블록을 벗어나면 풀로 돌아감
        f->samples[0] = i;
        check += f->id;
    }
    auto t1{ clock::now() };
    for (int i{ 0 }; i < rounds; ++i) {
        auto f{ std::make_unique<Frame>(i) };
        f->samples[0] = i;
        check += f->id;
    }
    auto t2{ clock::now() };

    using ms = std::chrono::duration<double, std::milli>;
    std::println("풀: 덩어리 할당 {}번, {:.2f}ms", pool.chunks(),
                 ms{ t1 - t0 }.count());
    std::println("new/delete: 할당 {}번, {:.2f}ms", rounds,
                 ms{ t2 - t1 }.count());
    std::println("검사 값 {}", check);
}
