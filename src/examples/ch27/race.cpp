#include <atomic>
#include <cstddef>
#include <new>
#include <print>
#include <thread>

// 주의: plain(보통 int)을 두 스레드가 함께 고치는 것은 데이터 경쟁이라
// 정의되지 않은 동작이다. "갱신이 사라지는" 현상을 보이려고 일부러 쓴다.
int plain{ 0 };
std::atomic<int> safe{ 0 };

void add(int times)
{
    for (int i{ 0 }; i < times; ++i) {
        plain = plain + 1;   // 읽고, 더하고, 쓰기: 중간에 끼어들 수 있다.
        ++safe;              // 원자적 증가: 끼어들 수 없다(4편).
    }
}

// 거짓 공유를 피하는 배치: 자주 쓰는 카운터를 서로 다른 캐시 줄에 둔다.
struct Packed {
    std::atomic<int> a;
    std::atomic<int> b;          // a와 같은 캐시 줄에 있을 가능성이 크다.
};
struct Spread {
    alignas(std::hardware_destructive_interference_size) std::atomic<int> a;
    alignas(std::hardware_destructive_interference_size) std::atomic<int> b;
};

int main()
{
    const int n{ 200'000 };
    std::thread t1{ add, n };
    std::thread t2{ add, n };
    t1.join();
    t2.join();
    std::println("기대값 {}, plain {}, atomic {}", 2 * n, plain, safe.load());

    std::println("캐시 줄 권장 간격 {}바이트",
                 std::hardware_destructive_interference_size);
    std::println("Packed {}바이트, Spread {}바이트", sizeof(Packed),
                 sizeof(Spread));
    std::println("하드웨어 스레드 수(추정) {}",
                 std::thread::hardware_concurrency());
}
