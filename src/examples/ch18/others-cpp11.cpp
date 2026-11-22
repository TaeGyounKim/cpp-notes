#include <bitset>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// 비멤버 std::begin/std::end는 C++11부터, cbegin/cend는 C++14부터,
// append_range는 C++23부터 있다. bitset은 C++98부터 있다.
int main()
{
    int raw[] = { 3, 1, 4, 1, 5 };
    std::vector<int> v;
    v.insert(v.end(), std::begin(raw), std::end(raw));
    v.insert(v.end(), raw, raw + 5);           // 포인터가 곧 반복자
    std::cout << v.size() << ' ';

    std::string word;
    word.push_back('h');
    word.insert(word.end(), 'i');
    std::cout << word << ' ';

    std::bitset<10> bits;
    bits.set(3).set(6);
    bits[8] = true;
    std::bitset<10> mask(std::string("0000111100"));
    std::cout << (bits & mask) << ' ' << bits.count() << '\n';
}
