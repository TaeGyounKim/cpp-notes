#include <cstddef>
#include <print>
#include <type_traits>
#include <vector>

// N차원 표: 원소 타입이 "한 차원 낮은 NDTable"이다(재귀 단계).
template <typename T, std::size_t N>
class NDTable {
public:
    static constexpr std::size_t rank{ N };
    explicit NDTable(std::size_t size = 3) { resize(size); }
    NDTable<T, N - 1>& operator[](std::size_t i) { return m_items[i]; }
    const NDTable<T, N - 1>& operator[](std::size_t i) const
    {
        return m_items[i];
    }
    // 모든 차원을 같은 크기로: 원소마다 한 차원 낮은 표를 size로 만든다.
    void resize(std::size_t size)
    {
        m_items.resize(size, NDTable<T, N - 1>{ size });
    }
    std::size_t size() const { return m_items.size(); }
    // 모든 원소 수: 재귀로 센다.
    std::size_t total() const { return size() * m_items.front().total(); }
private:
    std::vector<NDTable<T, N - 1>> m_items;
};

// 기저: 1차원이면 원소 타입이 T다(부분 특수화로 재귀를 멈춘다).
// 특수화는 기본 템플릿의 코드를 물려받지 않으므로 다시 써야 한다.
template <typename T>
class NDTable<T, 1> {
public:
    static constexpr std::size_t rank{ 1 };
    explicit NDTable(std::size_t size = 3) { resize(size); }
    T& operator[](std::size_t i) { return m_items[i]; }
    const T& operator[](std::size_t i) const { return m_items[i]; }
    void resize(std::size_t size) { m_items.resize(size); }
    std::size_t size() const { return m_items.size(); }
    std::size_t total() const { return size(); }
private:
    std::vector<T> m_items;
};

int main()
{
    NDTable<int, 3> cube{ 4 };            // 4 x 4 x 4
    cube[2][1][3] = 7;
    cube[0][0][0] = 1;
    std::println("rank {}, total {}", cube.rank, cube.total());
    std::println("{} {} {}", cube[2][1][3], cube[0][0][0], cube[3][3][3]);

    // cube[2]의 타입은 NDTable<int, 2>, cube[2][1]은 NDTable<int, 1>
    std::println("{} {}", std::remove_cvref_t<decltype(cube[2])>::rank,
                 std::remove_cvref_t<decltype(cube[2][1])>::rank);

    NDTable<char, 2> board{ 3 };          // 3 x 3
    for (std::size_t r{ 0 }; r < 3; ++r) {
        for (std::size_t c{ 0 }; c < 3; ++c) { board[r][c] = '.'; }
    }
    board[1][1] = 'X';
    for (std::size_t r{ 0 }; r < 3; ++r) {
        std::println("{}{}{}", board[r][0], board[r][1], board[r][2]);
    }
}
