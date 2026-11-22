#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <print>
#include <ranges>
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
    // 양방향 반복자가 있으면 거꾸로도 훑을 수 있다(가역 컨테이너).
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // 생성자들. 하나라도 직접 쓰면 기본 생성자도 써야 한다.
    directed_graph() = default;
    directed_graph(std::initializer_list<T> values) { assign(values); }
    template <std::input_iterator It>
    directed_graph(It first, It last) { assign(first, last); }

    // 복사 후 교환: 새 그래프를 다 만든 뒤 예외 없는 swap으로 바꿔 낀다.
    directed_graph& operator=(std::initializer_list<T> values)
    {
        directed_graph fresh{ values };
        swap(fresh);
        return *this;
    }

    template <std::input_iterator It>
    void assign(It first, It last)
    {
        clear();
        insert(first, last);
    }
    void assign(std::initializer_list<T> values)
    {
        assign(values.begin(), values.end());
    }

    iterator begin() const noexcept { return iterator{ m_nodes.begin() }; }
    iterator end() const noexcept { return iterator{ m_nodes.end() }; }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }
    reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator{ end() };
    }
    reverse_iterator rend() const noexcept
    {
        return reverse_iterator{ begin() };
    }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend() const noexcept { return rend(); }

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

    void insert(std::initializer_list<T> values)
    {
        insert(values.begin(), values.end());
    }
    template <std::ranges::input_range R>
    void insert_range(R&& range)      // C++23 컨테이너들처럼
    {
        insert(std::ranges::begin(range), std::ranges::end(range));
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

    // set처럼 값으로 지우고, 지운 개수(0 또는 1)를 돌려준다.
    size_type erase(const T& value)
    {
        auto it{ find(value) };
        if (it == end()) { return 0; }
        erase(it);
        return 1;
    }

    void clear() noexcept { m_nodes.clear(); }
    void swap(directed_graph& other) noexcept { m_nodes.swap(other.m_nodes); }
    size_type size() const noexcept { return m_nodes.size(); }
    bool empty() const noexcept { return m_nodes.empty(); }

    // 이웃 노드의 값을 복사하지 않고 훑는 뷰. 없는 노드면 빈 범위
    auto adjacent(const T& value) const
    {
        static const std::set<size_type> none;
        auto it{ find(value) };
        const auto& targets{ it == end() ? none : m_nodes[index(it)].targets };
        return targets | std::views::transform(
            [this](size_type i) -> const T& { return m_nodes[i].value; });
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

// 인접 노드 뷰 덕분에 출력 함수가 짧아진다.
template <typename T>
void print_graph(const directed_graph<T>& g)
{
    for (const auto& v : g) {
        std::print("{} ->", v);
        for (const auto& n : g.adjacent(v)) { std::print(" {}", n); }
        std::println("");
    }
}

int main()
{
    directed_graph g{ 10, 20, 30 };          // initializer_list + CTAD
    g.insert({ 40, 50 });
    g.insert_range(std::vector{ 60, 20 });   // 20은 이미 있음
    g.insert_edge(10, 20);
    g.insert_edge(10, 30);
    g.insert_edge(30, 60);
    print_graph(g);

    std::print("거꾸로:");
    for (auto it{ g.rbegin() }; it != g.rend(); ++it) {
        std::print(" {}", *it);
    }
    std::println("");
    std::println("views::reverse: {}", g | std::views::reverse
                                         | std::ranges::to<std::vector>());

    auto erased{ g.erase(20) };
    auto none{ g.erase(99) };
    std::println("erase(20) {}, erase(99) {}", erased, none);
    print_graph(g);

    g = { 1, 2 };                            // 대입도 initializer_list로
    std::vector<int> src{ 7, 8, 9 };
    directed_graph<int> h(src.begin(), src.end());
    std::println("g {} / h {}", g | std::ranges::to<std::vector>(),
                 h | std::ranges::to<std::vector>());
}
