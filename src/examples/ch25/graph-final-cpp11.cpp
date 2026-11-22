#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>

// initializer_list 생성자와 std::reverse_iterator는 C++11부터 있다.
// 뷰(C++20), insert_range(C++23), CTAD(C++17)는 없으므로 타입을 적는다.
template <typename T>
class value_list {
public:
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    value_list() {}
    value_list(std::initializer_list<T> values) : m_values(values) {}
    value_list& operator=(std::initializer_list<T> values)
    {
        value_list fresh(values);      // 복사 후 교환
        m_values.swap(fresh.m_values);
        return *this;
    }

    const_iterator begin() const { return m_values.begin(); }
    const_iterator end() const { return m_values.end(); }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

private:
    std::vector<T> m_values;
};

int main()
{
    value_list<int> g = { 10, 20, 30 };
    for (auto it = g.rbegin(); it != g.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    g = { 1, 2 };
    for (int v : g) { std::cout << v << ' '; }
    std::cout << '\n';
}
