#include <cstddef>
#include <iterator>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// 차례대로 돌아가며 하나씩 내주는 순번표. 원소를 넣고 빼도 안전하도록
// 반복자 대신 위치(인덱스)를 기억한다.
template <typename T>
class TurnTaker
{
public:
    explicit TurnTaker(std::size_t expected = 0) { m_items.reserve(expected); }

    void add(const T& item) { m_items.push_back(item); }   // 재할당돼도 안전

    void remove(const T& item)
    {
        for (std::size_t i{ 0 }; i < m_items.size(); ++i) {
            if (m_items[i] == item) {
                m_items.erase(m_items.begin() + i);
                if (i < m_next) { --m_next; }             // 앞쪽이 빠지면 당김
                if (m_next >= m_items.size()) { m_next = 0; }
                return;
            }
        }
    }

    T& next()
    {
        if (m_items.empty()) { throw std::out_of_range{ "순번이 비었음" }; }
        T& current{ m_items[m_next] };
        m_next = (m_next + 1) % m_items.size();
        return current;
    }

private:
    std::vector<T> m_items;
    std::size_t m_next{ 0 };
};

std::vector<int> makeSeries(std::size_t n)
{
    std::vector<int> v(n);
    for (int k{ 0 }; auto& x : v) { x = k++; }   // C++20 범위 for 초기화문
    return v;                                     // 복사 없이 이동(또는 생략)
}

int main()
{
    // 크기와 용량: 용량이 모자랄 때만 재할당한다.
    std::vector<int> v;
    std::size_t lastCap{ v.capacity() };
    for (int i{ 0 }; i < 20; ++i) {
        v.push_back(i);
        if (v.capacity() != lastCap) {
            std::print("{}→{} ", lastCap, v.capacity());
            lastCap = v.capacity();
        }
    }
    std::println("\n크기 {} 용량 {}", v.size(), v.capacity());
    // size()는 부호 없음, ssize()는 부호 있음(C++20)
    std::println("size()-21 = {}, ssize()-21 = {}", v.size() - 21,
                 std::ssize(v) - 21);

    std::vector<int> r;
    r.reserve(100);                              // 원소는 만들지 않는다.
    std::println("reserve 뒤 크기 {} 용량 {}", r.size(), r.capacity());

    v.clear();                                   // 크기만 0
    std::println("clear 뒤 크기 {} 용량 {}", v.size(), v.capacity());
    v.shrink_to_fit();                           // 요청일 뿐
    std::println("shrink_to_fit 뒤 용량 {}", v.capacity());
    std::vector<int>(20).swap(r);                // 맞바꿔 옛 메모리를 버림
    std::println("swap 뒤 r 용량 {}", r.capacity());

    int* raw{ r.data() };                        // 연속 메모리의 시작
    std::println("data()[0] = {}", raw[0]);

    auto series{ makeSeries(5) };
    std::println("{}", series);

    TurnTaker<std::string> turns{ 3 };
    turns.add("민수");
    turns.add("지은");
    turns.add("하늘");
    for (int i{ 0 }; i < 4; ++i) { std::print("{} ", turns.next()); }
    turns.remove("지은");
    std::print("| 지은 빠짐 | ");
    for (int i{ 0 }; i < 4; ++i) { std::print("{} ", turns.next()); }
    std::println("");

    // vector<bool>: 비트로 압축하고, 원소 대신 대리 객체를 돌려준다.
    std::vector<bool> lights{ true, false, true };
    lights.flip();                               // 모두 뒤집기
    lights[0].flip();                            // 하나만 뒤집기
    auto proxy{ lights[1] };                     // bool이 아니라 대리 객체
    proxy = false;                               // 원본이 바뀐다!
    // bool& ref{ lights[0] };                   // 오류: 진짜 bool이 아님
    std::println("{}", lights);
}
