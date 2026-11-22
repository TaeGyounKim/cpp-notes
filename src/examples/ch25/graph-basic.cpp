#include <algorithm>
#include <cstddef>
#include <optional>
#include <print>
#include <set>
#include <string>
#include <utility>
#include <vector>

// 방향 그래프: 노드마다 값 하나와, 나가는 간선이 가리키는 노드의 인덱스 집합
// (인접 리스트). 값은 그래프 안에서 서로 달라야 한다.
template <typename T>
class directed_graph {
public:
    bool insert(T value)
    {
        if (index_of(value)) { return false; }          // 이미 있음
        m_nodes.push_back(node{ std::move(value), {} });
        return true;
    }

    bool insert_edge(const T& from, const T& to)
    {
        auto f{ index_of(from) };
        auto t{ index_of(to) };
        if (!f || !t) { return false; }
        return m_nodes[*f].targets.insert(*t).second;   // 새로 생겼으면 true
    }

    bool erase_edge(const T& from, const T& to)
    {
        auto f{ index_of(from) };
        auto t{ index_of(to) };
        if (!f || !t) { return false; }
        return m_nodes[*f].targets.erase(*t) == 1;
    }

    bool erase(const T& value)
    {
        auto k{ index_of(value) };
        if (!k) { return false; }
        // 1) 모든 노드에서 k로 가는 간선을 없애고,
        //    k보다 큰 인덱스는 하나씩 줄인다.
        for (node& n : m_nodes) {
            std::set<std::size_t> shifted;
            for (std::size_t i : n.targets) {
                if (i < *k) { shifted.insert(i); }
                else if (i > *k) { shifted.insert(i - 1); }
            }
            n.targets = std::move(shifted);
        }
        // 2) 노드 자체를 지운다. 뒤의 노드들이 한 칸씩 앞으로 온다.
        m_nodes.erase(m_nodes.begin() + static_cast<std::ptrdiff_t>(*k));
        return true;
    }

    void clear() noexcept { m_nodes.clear(); }
    std::size_t size() const noexcept { return m_nodes.size(); }
    const T& operator[](std::size_t i) const { return m_nodes[i].value; }
    void swap(directed_graph& other) noexcept { m_nodes.swap(other.m_nodes); }

    std::set<T> adjacent_values(const T& value) const
    {
        auto k{ index_of(value) };
        return k ? values_of(m_nodes[*k].targets) : std::set<T>{};
    }

    // 노드를 넣은 순서와 상관없이, 같은 노드와 같은 간선이면 같다.
    bool operator==(const directed_graph& rhs) const
    {
        if (size() != rhs.size()) { return false; }
        return std::ranges::all_of(m_nodes, [&](const node& n) {
            return rhs.index_of(n.value)
                && values_of(n.targets) == rhs.adjacent_values(n.value);
        });
    }

private:
    struct node {
        T value;
        std::set<std::size_t> targets;
    };
    std::vector<node> m_nodes;

    std::optional<std::size_t> index_of(const T& value) const
    {
        auto it{ std::ranges::find(m_nodes, value, &node::value) };
        if (it == m_nodes.end()) { return std::nullopt; }
        return static_cast<std::size_t>(it - m_nodes.begin());
    }

    std::set<T> values_of(const std::set<std::size_t>& indices) const
    {
        std::set<T> values;
        for (std::size_t i : indices) { values.insert(m_nodes[i].value); }
        return values;
    }
};

template <typename T>
void swap(directed_graph<T>& a, directed_graph<T>& b) noexcept { a.swap(b); }

template <typename T>
void print_graph(const directed_graph<T>& g)
{
    for (std::size_t i{ 0 }; i < g.size(); ++i) {
        std::println("  [{}] {} -> {}", i, g[i], g.adjacent_values(g[i]));
    }
}

int main()
{
    directed_graph<std::string> g;
    for (const char* v : { "A", "B", "C", "D" }) { g.insert(v); }
    std::println("insert A again: {}", g.insert("A"));
    g.insert_edge("A", "B");
    g.insert_edge("A", "C");
    g.insert_edge("B", "C");
    g.insert_edge("C", "A");
    g.insert_edge("D", "C");
    std::println("edge to X: {}", g.insert_edge("A", "X"));
    print_graph(g);

    g.erase("B");                 // C와 D의 인덱스가 하나씩 당겨진다.
    std::println("B를 지운 뒤");
    print_graph(g);

    directed_graph<std::string> h;
    for (const char* v : { "D", "C", "A" }) { h.insert(v); }
    h.insert_edge("D", "C");
    h.insert_edge("C", "A");
    h.insert_edge("A", "C");
    std::println("g == h? {}", g == h);
    h.erase_edge("A", "C");
    std::println("간선 하나 지운 뒤 g == h? {}", g == h);
}
