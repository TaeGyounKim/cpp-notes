#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// 선택적 인스턴스화와 명시적 인스턴스화는 C++98부터 같은 규칙이다.
template <typename T>
class Bag
{
public:
    void add(const T& item) { m_items.push_back(item); }
    std::size_t size() const { return m_items.size(); }
    T total() const
    {
        T sum{};
        for (const auto& item : m_items) { sum = sum + item; }
        return sum;
    }

private:
    std::vector<T> m_items;
};

struct Tag { std::string name; };

template class Bag<std::string>;

int main()
{
    Bag<int> numbers;
    numbers.add(3);
    numbers.add(4);
    std::cout << numbers.total() << '\n';

    Bag<Tag> tags;          // total()을 부르지 않으므로 괜찮다.
    tags.add(Tag{ "거실" });
    std::cout << tags.size() << '\n';
}
