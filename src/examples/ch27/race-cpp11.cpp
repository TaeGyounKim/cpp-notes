#include <atomic>
#include <iostream>
#include <thread>

// std::thread, std::atomic, alignas는 C++11부터 있다.
// hardware_destructive_interference_size(C++17)가 없으므로 흔한 값 64를 쓴다.
std::atomic<int> safe(0);

void add(int times)
{
    for (int i = 0; i < times; ++i) { ++safe; }
}

struct Spread {
    alignas(64) std::atomic<int> a;
    alignas(64) std::atomic<int> b;
};

int main()
{
    std::thread t1(add, 200000);
    std::thread t2(add, 200000);
    t1.join();
    t2.join();
    std::cout << safe.load() << ' ' << sizeof(Spread) << '\n';
}
