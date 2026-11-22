#include <cstddef>
#include <print>
#include <string>
#include <vector>

template <typename T>
class Bag
{
public:
    void add(const T& item) { m_items.push_back(item); }
    std::size_t size() const { return m_items.size(); }

    // T에 +와 T{}가 있어야 컴파일되는 멤버
    T total() const
    {
        T sum{};
        for (const auto& item : m_items) { sum = sum + item; }
        return sum;
    }

private:
    std::vector<T> m_items;
};

struct Tag            // +가 없는 타입
{
    std::string name;
};

int main()
{
    Bag<int> numbers;
    numbers.add(3);
    numbers.add(4);
    std::println("{}개, 합 {}", numbers.size(), numbers.total());

    Bag<std::string> words;          // std::string에는 +가 있다.
    words.add("온도");
    words.add("센서");
    std::println("{}", words.total());

    // Tag에는 +가 없지만, total()을 부르지 않으므로 컴파일된다.
    Bag<Tag> tags;
    tags.add({ "거실" });
    std::println("태그 {}개", tags.size());
    // tags.total();   // 이 줄을 살리면 컴파일 오류
}

// 명시적 인스턴스화: 쓰지 않는 멤버까지 모두 컴파일해 본다.
template class Bag<std::string>;   // 문제없음
// template class Bag<Tag>;        // 살리면 total() 때문에 오류
