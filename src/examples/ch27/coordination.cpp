#include <atomic>
#include <barrier>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <latch>
#include <mutex>
#include <print>
#include <queue>
#include <semaphore>
#include <string>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

// 1) 조건 변수: 큐에 일이 들어올 때까지 작업자가 잠든다.
class JobQueue {
public:
    void push(int job)
    {
        {
            std::lock_guard lock{ m_mutex };
            m_jobs.push(job);
        }
        m_cv.notify_one();                 // 락 밖에서 알려도 된다.
    }
    void close()
    {
        {
            std::lock_guard lock{ m_mutex };
            m_closed = true;
        }
        m_cv.notify_all();
    }
    // 일이 있으면 꺼내고 true, 닫혔고 비었으면 false
    bool pop(int& job)
    {
        std::unique_lock lock{ m_mutex };
        // 술어가 참이 될 때까지 기다린다. 가짜로 깨어나도 다시 잠든다.
        m_cv.wait(lock, [this] { return !m_jobs.empty() || m_closed; });
        if (m_jobs.empty()) { return false; }
        job = m_jobs.front();
        m_jobs.pop();
        return true;
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<int> m_jobs;
    bool m_closed{ false };
};

void say(const std::string& s) { std::osyncstream{ std::cout } << s << '\n'; }

int main()
{
    JobQueue queue;
    int done{ 0 };
    {
        std::jthread worker{ [&] {
            int job{};
            while (queue.pop(job)) { done += job; }
        } };
        for (int i{ 1 }; i <= 10; ++i) { queue.push(i); }
        queue.close();
    }
    std::println("조건 변수: 처리한 합 {}", done);

    // 2) 래치: 일회용 카운트다운. 0이 되면 기다리던 쪽이 풀린다.
    std::latch finished{ 3 };
    std::atomic<int> parts{ 0 };
    std::vector<std::jthread> workers;
    for (int i{ 0 }; i < 3; ++i) {
        workers.emplace_back([&] { ++parts; finished.count_down(); });
    }
    finished.wait();                       // 셋 모두 끝날 때까지
    std::println("래치: 끝난 조각 {}", parts.load());
    workers.clear();

    // 3) 배리어: 여러 번 쓸 수 있는 집결 지점. 단계마다 완료 함수가 한 번 돈다.
    int round{ 1 };
    std::barrier sync{ 2, [&]() noexcept {
        say("  -- 단계 " + std::to_string(round++) + " 끝 --");
    } };
    {
        std::vector<std::jthread> robots;
        for (int r{ 0 }; r < 2; ++r) {
            robots.emplace_back([&, r] {
                for (int step{ 0 }; step < 2; ++step) {
                    say("로봇 " + std::to_string(r) + " 작업");
                    sync.arrive_and_wait();   // 둘 다 올 때까지 기다림
                }
            });
        }
    }

    // 4) 세마포어: 동시에 들어갈 수 있는 수를 제한한다(여기서는 2).
    std::counting_semaphore<2> slots{ 2 };
    std::atomic<int> inside{ 0 }, peak{ 0 };
    {
        std::vector<std::jthread> users;
        for (int i{ 0 }; i < 6; ++i) {
            users.emplace_back([&] {
                slots.acquire();
                int now{ ++inside };
                int old{ peak.load() };
                while (now > old && !peak.compare_exchange_weak(old, now)) {}
                std::this_thread::sleep_for(20ms);
                --inside;
                slots.release();
            });
        }
    }
    std::println("세마포어: 동시에 들어간 최대 {}", peak.load());
}
