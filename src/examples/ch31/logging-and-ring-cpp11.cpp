#include <cstddef>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// source_location(C++20) 대신 매크로가 __func__와 __LINE__을 넘긴다.
// std::format(C++20) 대신 ostringstream을 쓴다.
class TraceRing {
public:
    explicit TraceRing(std::size_t capacity)
        : m_items(capacity), m_next(0), m_count(0) {}

    void add(const std::string& message)
    {
        std::ostringstream os;
        os << '#' << m_count << ' ' << message;
        m_items[m_next] = os.str();
        m_next = (m_next + 1) % m_items.size();
        ++m_count;
    }

    void dump() const
    {
        std::size_t n = m_count < m_items.size() ? m_count : m_items.size();
        std::size_t start = m_count < m_items.size() ? 0 : m_next;
        std::printf("--- last %u traces ---\n", static_cast<unsigned>(n));
        for (std::size_t i = 0; i < n; ++i) {
            std::printf("  %s\n",
                        m_items[(start + i) % m_items.size()].c_str());
        }
    }

private:
    std::vector<std::string> m_items;
    std::size_t m_next;
    std::size_t m_count;
};

TraceRing g_ring(5);

void trace_at(const char* func, int line, const std::string& message)
{
    std::ostringstream os;
    os << func << ':' << line << ' ' << message;
    g_ring.add(os.str());
}
#define TRACE(msg) trace_at(__func__, __LINE__, (msg))

int parse_quantity(const std::string& text)
{
    TRACE("parse '" + text + "'");
    return std::stoi(text);
}

int main()
{
    const char* lines[] = { "2", "5", "x7", "1" };
    int total = 0;
    try {
        for (int i = 0; i < 4; ++i) { total += parse_quantity(lines[i]); }
        std::printf("total %d\n", total);
    } catch (const std::exception& e) {
        std::printf("[ERROR] %s\n", e.what());
        g_ring.dump();
    }
}
