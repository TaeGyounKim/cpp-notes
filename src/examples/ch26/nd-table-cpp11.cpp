#include <cstddef>
#include <iostream>
#include <vector>

// 템플릿 재귀와 부분 특수화는 C++98부터 된다.
// C++17 전에는 static constexpr 멤버가 인라인 변수가 아니어서,
// cout << rank처럼 참조로 넘기면 링크 오류가 날 수 있다. 함수로 돌려준다.
template <typename T, std::size_t N>
class NDTable {
public:
    explicit NDTable(std::size_t size = 3) { resize(size); }
    NDTable<T, N - 1>& operator[](std::size_t i) { return m_items[i]; }
    void resize(std::size_t size)
    {
        m_items.resize(size, NDTable<T, N - 1>(size));
    }
    static std::size_t rank() { return N; }
private:
    std::vector<NDTable<T, N - 1> > m_items;
};

template <typename T>
class NDTable<T, 1> {
public:
    explicit NDTable(std::size_t size = 3) { resize(size); }
    T& operator[](std::size_t i) { return m_items[i]; }
    void resize(std::size_t size) { m_items.resize(size); }
    static std::size_t rank() { return 1; }
private:
    std::vector<T> m_items;
};

int main()
{
    NDTable<int, 3> cube(4);
    cube[2][1][3] = 7;
    std::cout << cube.rank() << ' ' << cube[2][1][3] << ' ' << cube[3][3][3]
              << '\n';
}
