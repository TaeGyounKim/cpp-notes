#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// 콘셉트, == 기본 정의(C++20)가 없으므로 ==, !=를 직접 쓰고,
// 반복자 특성(iterator_category 등)만으로 표준 알고리즘과 맞춘다.
template <typename T>
class value_list {
    typedef typename std::vector<T>::const_iterator inner;

public:
    class const_iterator {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        const_iterator() : m_it() {}
        explicit const_iterator(inner it) : m_it(it) {}
        reference operator*() const { return *m_it; }
        pointer operator->() const { return &*m_it; }
        const_iterator& operator++() { ++m_it; return *this; }
        const_iterator operator++(int)
        {
            const_iterator old(*this);
            ++m_it;
            return old;
        }
        const_iterator& operator--() { --m_it; return *this; }
        bool operator==(const const_iterator& o) const
        {
            return m_it == o.m_it;
        }
        bool operator!=(const const_iterator& o) const
        {
            return m_it != o.m_it;
        }

    private:
        inner m_it;
    };

    void push(const T& v) { m_values.push_back(v); }
    const_iterator begin() const { return const_iterator(m_values.begin()); }
    const_iterator end() const { return const_iterator(m_values.end()); }

private:
    std::vector<T> m_values;
};

int main()
{
    value_list<std::string> g;
    g.push("seoul");
    g.push("busan");
    g.push("jeju");
    for (const std::string& c : g) { std::cout << c << ' '; }
    std::cout << '\n';
    auto five = [](const std::string& c) { return c.size() == 5; };
    std::cout << std::count_if(g.begin(), g.end(), five) << ' '
              << *std::prev(g.end()) << '\n';
}
