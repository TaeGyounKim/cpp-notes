#include <algorithm>
#include <cstddef>
#include <optional>
#include <print>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class directed_graph {
public:
    // 컨테이너라면 갖춰야 하는 타입 별칭(반복자 둘은 다음 글에서)
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    bool insert(T value)
    {
        if (index_of(value)) { return false; }
        m_nodes.push_back(node{ std::move(value), {} });
        return true;
    }

    // 필수 멤버 함수 중 크기에 관한 것: m_nodes에 넘긴다.
    size_type size() const noexcept { return m_nodes.size(); }
    size_type max_size() const noexcept { return m_nodes.max_size(); }
    bool empty() const noexcept { return m_nodes.empty(); }

    const_reference operator[](size_type i) const { return m_nodes[i].value; }
    // 범위를 검사하는 접근: 벗어나면 out_of_range
    const_reference at(size_type i) const { return m_nodes.at(i).value; }

    bool operator==(const directed_graph&) const = default;   // 간단히
    void swap(directed_graph& other) noexcept { m_nodes.swap(other.m_nodes); }

private:
    struct node {
        T value;
        std::set<size_type> targets;
        bool operator==(const node&) const = default;
    };
    std::vector<node> m_nodes;

    std::optional<size_type> index_of(const T& value) const
    {
        auto it{ std::ranges::find(m_nodes, value, &node::value) };
        if (it == m_nodes.end()) { return std::nullopt; }
        return static_cast<size_type>(it - m_nodes.begin());
    }
};

// 컨테이너의 타입 별칭만 믿고 쓰는 제네릭 함수: vector와 그래프 모두 된다.
template <typename Container>
typename Container::value_type first_or(const Container& c,
                                        typename Container::value_type fallback)
{
    typename Container::size_type n{ c.size() };
    return n == 0 ? fallback : c[0];
}

int main()
{
    directed_graph<std::string> g;
    std::println("empty {}, size {}", g.empty(), g.size());
    g.insert("A");
    g.insert("B");
    std::println("empty {}, size {}, max_size > 0? {}", g.empty(), g.size(),
                 g.max_size() > 0);

    std::println("first_or(g) {}", first_or(g, std::string{ "-" }));
    std::println("first_or(vector) {}", first_or(std::vector{ 7, 8 }, 0));

    try {
        std::println("{}", g.at(5));
    } catch (const std::out_of_range&) {
        std::println("out_of_range: 인덱스 5는 범위 밖");
    }

    directed_graph<std::string> copy{ g };     // 0의 규칙: 복사가 그냥 된다.
    std::println("copy == g? {}", copy == g);
}
