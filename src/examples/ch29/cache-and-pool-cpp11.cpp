#include <cstddef>
#include <cstdio>
#include <memory>
#include <new>
#include <utility>
#include <vector>

// std::destroy_at(C++17) 대신 소멸자를 직접 부른다: p->~T()
// 가변 인자 템플릿과 완벽 전달은 C++11에도 있다.
template <typename T, std::size_t ChunkSize = 8>
class Pool {
public:
    struct Returner {
        Pool* pool;
        void operator()(T* p) const
        {
            p->~T();
            pool->m_free.push_back(p);
        }
    };
    typedef std::unique_ptr<T, Returner> Handle;

    Pool() {}
    ~Pool()
    {
        for (std::size_t i = 0; i < m_chunks.size(); ++i) {
            m_alloc.deallocate(m_chunks[i], ChunkSize);
        }
    }

    template <typename... Args>
    Handle acquire(Args&&... args)
    {
        if (m_free.empty()) { add_chunk(); }
        T* slot = m_free.back();
        T* obj = ::new (static_cast<void*>(slot))
            T(std::forward<Args>(args)...);
        m_free.pop_back();
        Returner r = { this };
        return Handle(obj, r);
    }
    std::size_t chunks() const { return m_chunks.size(); }

private:
    Pool(const Pool&);              // 복사 금지(C++03 방식)
    Pool& operator=(const Pool&);

    void add_chunk()
    {
        T* chunk = m_alloc.allocate(ChunkSize);
        m_chunks.push_back(chunk);
        for (std::size_t i = 0; i < ChunkSize; ++i) {
            m_free.push_back(chunk + i);
        }
    }

    std::allocator<T> m_alloc;
    std::vector<T*> m_chunks;
    std::vector<T*> m_free;
};

struct Frame {
    explicit Frame(int i) : id(i) {}
    int id;
    double samples[64 * 1024];
};

int main()
{
    Pool<Frame> pool;
    long long check = 0;
    for (int i = 0; i < 20000; ++i) {
        Pool<Frame>::Handle f = pool.acquire(i);
        f->samples[0] = i;
        check += f->id;
    }
    std::printf("chunks %u, check %lld\n",
                static_cast<unsigned>(pool.chunks()), check);
}
