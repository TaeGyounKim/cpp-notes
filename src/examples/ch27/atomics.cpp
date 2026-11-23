#include <atomic>
#include <chrono>
#include <memory>
#include <print>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

struct Small { int v; };
struct Big { int data[64]; };

// 원자적 곱하기: compare_exchange 반복문으로 직접 만든다.
void atomic_multiply(std::atomic<int>& a, int n)
{
    int expected{ a.load() };
    int desired{ expected * n };
    // a가 아직 expected이면 desired로 바꾸고 true.
    // 다른 스레드가 먼저 바꿨으면 expected에 지금 값을 넣고 false → 다시 계산
    while (!a.compare_exchange_strong(expected, desired)) {
        desired = expected * n;
    }
}

int main()
{
    // 1) 여러 스레드가 함께 늘리는 카운터: 지역에서 세고 마지막에 한 번 더한다.
    std::atomic<int> counter{ 0 };
    {
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 8; ++t) {
            threads.emplace_back([&counter] {
                int local{ 0 };
                for (int i{ 0 }; i < 1000; ++i) { ++local; }
                counter += local;          // 원자적 연산은 한 번만
            });
        }
    }
    std::println("counter {}", counter.load());

    // 2) fetch_add: 더하기 전 값을 돌려준다.
    std::atomic<int> value{ 10 };
    int before{ value.fetch_add(4) };
    std::println("fetch_add 전 {}, 후 {}", before, value.load());

    std::atomic<int> m{ 3 };
    atomic_multiply(m, 7);
    std::println("곱하기 {}", m.load());

    // 3) 잠금 없이 동작하는가
    std::println("int {}, Small {}, Big {}",
                 std::atomic<int>::is_always_lock_free,
                 std::atomic<Small>::is_always_lock_free,
                 std::atomic<Big>::is_always_lock_free);

    // 4) atomic_ref: 보통 변수를 원자적으로 다룬다(C++20).
    int plain{ 0 };
    {
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 4; ++t) {
            threads.emplace_back([&plain] {
                std::atomic_ref<int> ref{ plain };
                for (int i{ 0 }; i < 500; ++i) { ++ref; }
            });
        }
    }
    std::println("atomic_ref로 늘린 plain {}", plain);

    // 5) wait / notify: 값이 바뀔 때까지 효율적으로 기다린다(C++20).
    std::atomic<int> flag{ 0 };
    std::jthread waiter{ [&flag] {
        flag.wait(0);                      // 0인 동안 잠든다.
        std::println("깨어남: flag = {}", flag.load());
    } };
    std::this_thread::sleep_for(50ms);
    flag = 1;
    flag.notify_all();
}
