#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// condition_variable은 C++11부터 있다. latch, barrier, semaphore(C++20)는
// 없으므로 조건 변수와 카운터로 직접 만든다. 여기서는 래치 흉내를 낸다.
class CountDown {
public:
    explicit CountDown(int n) : m_count(n) {}
    void count_down()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (--m_count == 0) { m_cv.notify_all(); }
    }
    void wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return m_count == 0; });
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_count;
};

int main()
{
    CountDown done(3);
    std::thread a([&] { done.count_down(); });
    std::thread b([&] { done.count_down(); });
    std::thread c([&] { done.count_down(); });
    done.wait();
    std::cout << "all three finished\n";
    a.join();
    b.join();
    c.join();
}
