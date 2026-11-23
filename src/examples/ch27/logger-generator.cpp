#include <condition_variable>
#include <format>
#include <generator>
#include <mutex>
#include <print>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// 여러 스레드가 log()로 넣고, 백그라운드 스레드 하나가 차례로 쓰는 로거
class Logger {
public:
    Logger() : m_worker{ [this] { process(); } } {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    ~Logger()
    {
        {
            // process()가 검사와 wait 사이에 있을 때 알림을 놓치지 않도록
            std::lock_guard lock{ m_mutex };
            m_exit = true;
        }
        m_cv.notify_all();
        // jthread가 소멸하며 join한다(남은 항목을 다 쓴 뒤 끝난다).
    }
    void log(std::string entry)
    {
        {
            std::lock_guard lock{ m_mutex };
            m_queue.push(std::move(entry));
        }
        m_cv.notify_all();
    }
private:
    void process()
    {
        std::unique_lock lock{ m_mutex };
        while (true) {
            m_cv.wait(lock, [this] { return !m_queue.empty() || m_exit; });
            // 락을 쥔 동안에는 지역 큐와 바꾸기만 하고 바로 놓는다.
            std::queue<std::string> local;
            local.swap(m_queue);
            bool exiting{ m_exit };
            lock.unlock();
            while (!local.empty()) {           // 느린 출력은 락 밖에서
                std::println("[log] {}", local.front());
                local.pop();
            }
            if (exiting) { break; }            // 남은 것을 다 쓰고 끝
            lock.lock();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<std::string> m_queue;
    bool m_exit{ false };
    std::jthread m_worker;   // 마지막 멤버: 다른 멤버가 다 만들어진 뒤 시작
};

// 코루틴(C++23 std::generator): co_yield로 값을 내고 멈췄다가 다음에 이어 간다.
std::generator<int> squares(int n)
{
    for (int i{ 1 }; i <= n; ++i) {
        co_yield i * i;
    }
}

int main()
{
    {
        Logger logger;
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 3; ++t) {
            threads.emplace_back([&logger, t] {
                for (int i{ 0 }; i < 2; ++i) {
                    logger.log(std::format("스레드 {} 메시지 {}", t, i));
                }
            });
        }
    }   // threads가 먼저 끝나고, 그다음 logger가 남은 것을 쓰고 끝난다.

    std::print("제곱:");
    for (int v : squares(5)) { std::print(" {}", v); }   // 필요할 때마다 하나씩
    std::println("");
}
