#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

// thread, thread_local, std::ref는 C++11부터 있다.
// jthread와 stop_token(C++20)이 없으므로 atomic<bool> 깃발로 멈추게 하고,
// 소멸 전에 직접 join한다.
thread_local int mine = 0;

void touch(int id)
{
    ++mine;
    std::cout << "thread " << id << " mine=" << mine << '\n';
}

void worker(const std::atomic<bool>& stop)
{
    while (!stop.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    std::cout << "worker stopped\n";
}

int main()
{
    std::thread a(touch, 1);
    a.join();
    std::thread b(touch, 2);
    b.join();

    std::atomic<bool> stop(false);
    std::thread w(worker, std::cref(stop));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stop = true;
    w.join();
}
