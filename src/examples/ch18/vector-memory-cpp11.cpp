#include <iostream>
#include <vector>

// capacity, reserve, swap으로 메모리 돌려주기는 C++98부터,
// shrink_to_fit과 data()는 C++11부터 있다. ssize(C++20) 대신 형 변환을 쓴다.
std::vector<int> makeSeries(std::size_t n)
{
    std::vector<int> v(n);
    int k = 0;
    for (auto& x : v) { x = k++; }
    return v;                            // C++11부터 이동
}

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 20; ++i) { v.push_back(i); }
    std::cout << v.size() << ' ' << v.capacity() << ' '
              << static_cast<long>(v.size()) - 21 << '\n';

    v.clear();
    v.shrink_to_fit();
    std::vector<int> r;
    r.reserve(100);
    std::vector<int>(20).swap(r);
    std::cout << v.capacity() << ' ' << r.capacity() << ' ' << r.data()[0]
              << '\n';

    std::vector<int> series = makeSeries(5);
    std::vector<bool> lights = { true, false, true };
    lights.flip();
    std::cout << series.back() << ' ' << lights[0] << lights[1] << lights[2]
              << '\n';
}
