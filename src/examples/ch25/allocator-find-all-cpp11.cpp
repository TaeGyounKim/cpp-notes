#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <string>
#include <vector>

// 콘셉트(C++20), 센티널·프로젝션(C++20), invoke(C++17)가 없으므로
// 제약 없는 템플릿으로 쓰고 술어를 바로 부른다.
template <typename ForwardIt, typename OutputIt, typename Pred>
OutputIt find_all(ForwardIt first, ForwardIt last, OutputIt dest, Pred pred)
{
    for (; first != last; ++first) {
        if (pred(*first)) {
            *dest = first;
            ++dest;
        }
    }
    return dest;
}

int main()
{
    // construct_at(C++20), destroy_at(C++17) 대신 배치 new와 소멸자 직접 호출
    std::allocator<std::string> alloc;
    std::string* raw = alloc.allocate(1);
    ::new (static_cast<void*>(raw)) std::string("first");
    std::cout << *raw << '\n';
    raw->~basic_string();
    alloc.deallocate(raw, 1);

    std::vector<int> values = { 5, 4, 5, 4, 10, 6, 5, 8, 10 };
    std::vector<std::vector<int>::iterator> hits;
    find_all(values.begin(), values.end(), std::back_inserter(hits),
             [](int v) { return v == 10; });
    for (std::size_t i = 0; i < hits.size(); ++i) {
        std::cout << "10 at " << (hits[i] - values.begin()) << '\n';
    }
}
