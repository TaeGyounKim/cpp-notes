#include <iterator>
#include <list>
#include <print>
#include <vector>

// 입력 반복자 범위 [begin, end)의 원소를 출력한다.
template <std::input_iterator Iter>
void show(Iter begin, Iter end)
{
    for (auto it{ begin }; it != end; ++it) { std::print("{} ", *it); }
    std::println("");
}

// iterator_traits로 원소 타입을 알아낸다.
template <std::input_iterator Iter>
Iter findValue(Iter begin, Iter end,
               const typename std::iterator_traits<Iter>::value_type& value)
{
    for (auto it{ begin }; it != end; ++it) {
        if (*it == value) { return it; }
    }
    return end;
}

// 반복자 범주에 따라 다른 구현을 고른다(콘셉트 오버로드).
template <std::input_iterator Iter>
void moveBy(Iter& it, int n) { while (n-- > 0) { ++it; } }

template <std::bidirectional_iterator Iter>
void moveBy(Iter& it, int n)
{
    while (n > 0) { ++it; --n; }
    while (n < 0) { --it; ++n; }
}

template <std::random_access_iterator Iter>
void moveBy(Iter& it, int n) { it += n; }   // 한 번에 건너뛴다.

int main()
{
    std::vector<int> v{ 11, 22, 33, 44, 55 };
    std::list<int> l{ 1, 2, 3, 4, 5 };

    show(v.cbegin(), v.cend());                // const 반복자
    show(std::crbegin(v), std::crend(v));      // 거꾸로
    show(l.begin(), l.end());

    auto found{ findValue(std::cbegin(v), std::cend(v), 33) };
    if (found != std::cend(v)) {
        std::println("33의 위치 {}", std::distance(std::cbegin(v), found));
    }

    auto vi{ v.begin() };
    moveBy(vi, 3);                             // random_access 판
    auto li{ l.begin() };
    moveBy(li, 3);                             // bidirectional 판
    moveBy(li, -2);
    std::println("vector 3칸 뒤 {}, list 3칸 뒤 2칸 앞 {}", *vi, *li);

    std::println("vector 반복자는 연속? {}, list는? {}",
                 std::contiguous_iterator<std::vector<int>::iterator>,
                 std::contiguous_iterator<std::list<int>::iterator>);
}
