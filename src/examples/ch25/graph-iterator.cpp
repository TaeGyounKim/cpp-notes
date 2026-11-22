#include <algorithm>
#include <cstddef>
#include <iterator>
#include <print>
#include <set>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class directed_graph {
    struct node {
        T value;
        std::set<std::size_t> targets;
    };
    using node_iter = typename std::vector<node>::const_iterator;

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    // 노드 값을 넣은 순서로 훑는 양방향 반복자. vector의 반복자를 감싼다.
    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() = default;   // 기본 생성(가리키는 것 없음)
        reference operator*() const { return m_it->value; }
        pointer operator->() const { return &m_it->value; }
        const_iterator& operator++() { ++m_it; return *this; }
        const_iterator operator++(int)
        {
            auto old{ *this };
            ++m_it;
            return old;
        }
        const_iterator& operator--() { --m_it; return *this; }
        const_iterator operator--(int)
        {
            auto old{ *this };
            --m_it;
            return old;
        }
        bool operator==(const const_iterator&) const = default;

    private:
        friend class directed_graph;   // 그래프만 감싼 반복자를 만들고 꺼낸다.
        explicit const_iterator(node_iter it) : m_it{ it } {}
        node_iter m_it{};
    };
    using iterator = const_iterator;   // 값은 바꿀 수 없으므로 둘 다 const

    iterator begin() const noexcept { return iterator{ m_nodes.begin() }; }
    iterator end() const noexcept { return iterator{ m_nodes.end() }; }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    // 표준 컨테이너처럼: 넣은(또는 이미 있던) 원소의 반복자와 성공 여부
    std::pair<iterator, bool> insert(T value)
    {
        if (auto it{ find(value) }; it != end()) { return { it, false }; }
        m_nodes.push_back(node{ std::move(value), {} });
        return { std::prev(end()), true };
    }
    // 위치 힌트를 받는 판(insert_iterator가 부른다). 힌트는 무시한다.
    iterator insert(const_iterator, T value)
    {
        return insert(std::move(value)).first;
    }
    template <std::input_iterator It>
    void insert(It first, It last)
    {
        std::copy(first, last, std::inserter(*this, end()));
    }

    iterator find(const T& value) const
    {
        return iterator{ std::ranges::find(m_nodes, value, &node::value) };
    }

    bool insert_edge(const T& from, const T& to)
    {
        auto f{ find(from) };
        auto t{ find(to) };
        if (f == end() || t == end()) { return false; }
        return m_nodes[index(f)].targets.insert(index(t)).second;
    }

    // 지운 원소 다음 원소의 반복자를 돌려준다.
    iterator erase(const_iterator pos)
    {
        if (pos == end()) { return end(); }
        size_type k{ index(pos) };
        erase_at(k);
        return iterator{ m_nodes.begin() + static_cast<difference_type>(k) };
    }
    iterator erase(const_iterator first, const_iterator last)
    {
        size_type from{ index(first) };
        for (size_type k{ index(last) }; k > from; --k) { erase_at(k - 1); }
        return iterator{ m_nodes.begin() + static_cast<difference_type>(from) };
    }

    size_type size() const noexcept { return m_nodes.size(); }
    bool empty() const noexcept { return m_nodes.empty(); }

    std::set<T> adjacent_values(const T& value) const
    {
        std::set<T> result;
        if (auto it{ find(value) }; it != end()) {
            for (size_type i : m_nodes[index(it)].targets) {
                result.insert(m_nodes[i].value);
            }
        }
        return result;
    }

private:
    std::vector<node> m_nodes;

    size_type index(const_iterator it) const
    {
        return static_cast<size_type>(it.m_it - m_nodes.begin());
    }
    void erase_at(size_type k)
    {
        for (node& n : m_nodes) {
            std::set<size_type> shifted;
            for (size_type i : n.targets) {
                if (i < k) { shifted.insert(i); }
                else if (i > k) { shifted.insert(i - 1); }
            }
            n.targets = std::move(shifted);
        }
        m_nodes.erase(m_nodes.begin() + static_cast<difference_type>(k));
    }
};

// C++20 콘셉트로 반복자 요건을 컴파일 시간에 검사한다.
static_assert(
    std::bidirectional_iterator<directed_graph<int>::const_iterator>);

int main()
{
    directed_graph<std::string> g;
    auto [it, ok] { g.insert("seoul") };
    std::println("{} {}", *it, ok);
    std::println("again: {}", g.insert("seoul").second);

    std::vector<std::string> more{ "busan", "daegu", "incheon", "gwangju" };
    g.insert(more.begin(), more.end());      // 범위 삽입(insert_iterator)
    g.insert_edge("seoul", "busan");
    g.insert_edge("busan", "daegu");

    for (const auto& city : g) { std::print("{} ", city); }   // 범위 for
    std::println("");

    // 표준 알고리즘과 함께
    auto five{ [](const std::string& c) { return c.size() == 5; } };
    auto n{ std::ranges::count_if(g, five) };
    std::println("다섯 글자 {}개, 마지막 {}", n, *std::prev(g.end()));
    std::vector<std::string> copy(g.begin(), g.end());
    std::println("vector로 복사 {}", copy);

    auto pos{ g.find("daegu") };
    std::println("daegu를 지움 -> 다음 원소 {}", *g.erase(pos));
    g.erase(std::next(g.begin(), 2), std::next(g.begin(), 3));   // [2, 3)
    for (const auto& city : g) {
        std::println("{} -> {}", city, g.adjacent_values(city));
    }
}
