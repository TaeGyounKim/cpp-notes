#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

// optional(C++17)이 없으므로 "없음"을 size()로 나타내고,
// ranges::find의 프로젝션(C++20) 대신 반복문으로 찾는다.
template <typename T>
class directed_graph {
public:
    bool insert(T value)
    {
        if (index_of(value) != m_nodes.size()) { return false; }
        node n;
        n.value = std::move(value);
        m_nodes.push_back(std::move(n));
        return true;
    }
    bool insert_edge(const T& from, const T& to)
    {
        std::size_t f = index_of(from);
        std::size_t t = index_of(to);
        if (f == m_nodes.size() || t == m_nodes.size()) { return false; }
        return m_nodes[f].targets.insert(t).second;
    }
    std::size_t size() const { return m_nodes.size(); }
    const T& operator[](std::size_t i) const { return m_nodes[i].value; }
    std::set<T> adjacent_values(const T& value) const
    {
        std::set<T> values;
        std::size_t k = index_of(value);
        if (k == m_nodes.size()) { return values; }
        for (std::size_t i : m_nodes[k].targets) {
            values.insert(m_nodes[i].value);
        }
        return values;
    }

private:
    struct node {
        T value;
        std::set<std::size_t> targets;
    };
    std::vector<node> m_nodes;

    std::size_t index_of(const T& value) const
    {
        for (std::size_t i = 0; i < m_nodes.size(); ++i) {
            if (m_nodes[i].value == value) { return i; }
        }
        return m_nodes.size();
    }
};

int main()
{
    directed_graph<std::string> g;
    g.insert("A");
    g.insert("B");
    g.insert_edge("A", "B");
    for (std::size_t i = 0; i < g.size(); ++i) {
        std::cout << g[i] << " ->";
        std::set<std::string> adj = g.adjacent_values(g[i]);
        for (const std::string& v : adj) { std::cout << ' ' << v; }
        std::cout << '\n';
    }
}
