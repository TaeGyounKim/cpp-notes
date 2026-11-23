#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// atomic, compare_exchange, fetch_add, is_lock_free()는 C++11부터 있다.
// atomic_ref, wait/notify(C++20), is_always_lock_free(C++17)는 없다.
// 기다리기는 조건 변수(7편)나 주기적 확인으로 한다.
int main()
{
    std::atomic<int> counter(0);
    std::vector<std::thread> threads;
    for (int t = 0; t < 8; ++t) {
        threads.emplace_back([&counter] {
            int local = 0;
            for (int i = 0; i < 1000; ++i) { ++local; }
            counter += local;
        });
    }
    for (std::thread& th : threads) { th.join(); }

    std::atomic<int> m(3);
    int expected = m.load();
    while (!m.compare_exchange_strong(expected, expected * 7)) {}

    std::cout << counter.load() << ' ' << m.load() << ' '
              << std::boolalpha << m.is_lock_free() << '\n';
}
