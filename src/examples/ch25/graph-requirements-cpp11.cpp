#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 타입 별칭 using은 C++11부터다(그 전에는 typedef).
// == 기본 정의(C++20)는 없으므로 필요하면 직접 쓴다.
template <typename T>
class small_graph {
public:
    using value_type = T;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    void insert(const T& value) { m_values.push_back(value); }
    size_type size() const { return m_values.size(); }
    bool empty() const { return m_values.empty(); }
    const_reference operator[](size_type i) const { return m_values[i]; }
    const_reference at(size_type i) const { return m_values.at(i); }

private:
    std::vector<T> m_values;
};

template <typename Container>
typename Container::value_type first_or(
    const Container& c, typename Container::value_type fallback)
{
    return c.size() == 0 ? fallback : c[0];
}

int main()
{
    small_graph<std::string> g;
    std::cout << first_or(g, std::string("-")) << '\n';
    g.insert("A");
    std::cout << first_or(g, std::string("-")) << '\n';
    try {
        g.at(3);
    } catch (const std::out_of_range&) {
        std::cout << "out_of_range\n";
    }
}
