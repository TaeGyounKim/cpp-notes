#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// 콘셉트(C++20)가 없으므로 iterator_traits의 범주 태그로 구현을 고른다.
template <typename Iter>
void moveByImpl(Iter& it, int n, std::input_iterator_tag)
{
    while (n-- > 0) { ++it; }
}

template <typename Iter>
void moveByImpl(Iter& it, int n, std::bidirectional_iterator_tag)
{
    while (n > 0) { ++it; --n; }
    while (n < 0) { --it; ++n; }
}

template <typename Iter>
void moveByImpl(Iter& it, int n, std::random_access_iterator_tag)
{
    it += n;
}

template <typename Iter>
void moveBy(Iter& it, int n)
{
    typedef typename std::iterator_traits<Iter>::iterator_category category;
    moveByImpl(it, n, category());   // 태그 객체로 오버로드를 고른다.
}

int main()
{
    std::vector<int> v = { 11, 22, 33, 44, 55 };
    std::list<int> l = { 1, 2, 3, 4, 5 };
    std::vector<int>::iterator vi = v.begin();
    std::list<int>::iterator li = l.begin();
    moveBy(vi, 3);
    moveBy(li, 3);
    moveBy(li, -2);
    // 전역 std::begin/end는 C++11, cbegin/crbegin은 C++14부터
    std::cout << *vi << ' ' << *li << ' '
              << std::distance(std::begin(v), std::end(v)) << '\n';
}
