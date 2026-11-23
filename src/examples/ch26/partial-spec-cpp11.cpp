#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

// 부분 특수화와 함수 템플릿 오버로딩은 C++98부터 된다.
// make_unique(C++14), optional(C++17)이 없으므로 new와 "찾지 못함" 값을 쓴다.
template <typename T>
class Boxes {
public:
    explicit Boxes(std::size_t n) : m_items(n) {}
    T& at(std::size_t i) { return m_items[i]; }
private:
    std::vector<T> m_items;
};

template <typename U>
class Boxes<U*> {
public:
    explicit Boxes(std::size_t n) : m_items(n) {}
    Boxes(const Boxes& src) : m_items(src.m_items.size())
    {
        for (std::size_t i = 0; i < m_items.size(); ++i) {
            if (src.m_items[i]) { m_items[i].reset(new U(*src.m_items[i])); }
        }
    }
    std::unique_ptr<U>& at(std::size_t i) { return m_items[i]; }
private:
    std::vector<std::unique_ptr<U> > m_items;
};

const std::size_t npos = static_cast<std::size_t>(-1);

template <typename T>
std::size_t index_of(const T& v, const T* arr, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) { if (arr[i] == v) { return i; } }
    return npos;
}
template <typename T>
std::size_t index_of(T* v, T* const* arr, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) { if (*arr[i] == *v) { return i; } }
    return npos;
}

int main()
{
    Boxes<int*> a(1);
    a.at(0).reset(new int(10));
    Boxes<int*> b(a);
    *b.at(0) = 20;
    int x = 3, y = 3;
    int* ptrs[] = { &y };
    std::cout << *a.at(0) << ' ' << *b.at(0) << ' '
              << index_of(&x, ptrs, 1) << '\n';
}
