#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// jthread(C++20)가 없으므로 소멸자에서 직접 join한다.
// join을 빠뜨리면 joinable한 thread의 소멸자가 terminate를 부른다.
// 코루틴(C++20), std::generator(C++23)는 대신할 표준 기능이 없다.
class Logger {
public:
    Logger() : m_exit(false), m_worker(&Logger::process, this) {}
    ~Logger()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_exit = true;
        }
        m_cv.notify_all();
        m_worker.join();
    }
    void log(const std::string& entry)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(entry);
        }
        m_cv.notify_all();
    }
private:
    void process()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (true) {
            m_cv.wait(lock, [this] { return !m_queue.empty() || m_exit; });
            std::queue<std::string> local;
            local.swap(m_queue);
            bool exiting = m_exit;
            lock.unlock();
            for (; !local.empty(); local.pop()) {
                std::cout << "[log] " << local.front() << '\n';
            }
            if (exiting) { break; }
            lock.lock();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<std::string> m_queue;
    bool m_exit;
    std::thread m_worker;
};

int main()
{
    Logger logger;
    std::vector<std::thread> threads;
    for (int t = 0; t < 2; ++t) {
        threads.emplace_back([&logger, t] {
            std::ostringstream os;
            os << "thread " << t;
            logger.log(os.str());
        });
    }
    for (std::thread& th : threads) { th.join(); }
}
