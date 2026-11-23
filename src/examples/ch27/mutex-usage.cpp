#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <print>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

// 1) 동기화된 스트림: 한 줄을 여러 번에 나눠 써도 다른 스레드와 섞이지 않는다.
void report_sync(int id)
{
    for (int i{ 0 }; i < 3; ++i) {
        std::osyncstream out{ std::cout };   // 모아 두었다가
        out << "작업 " << id << ": " << i << '\n';
    }                                         // 소멸할 때 한꺼번에 내보낸다.
}

// 2) 뮤텍스로 보호: 모든 스레드가 같은 뮤텍스를 써야 하므로 static
class Reporter {
public:
    explicit Reporter(int id) : m_id{ id } {}
    void operator()() const
    {
        for (int i{ 0 }; i < 3; ++i) {
            std::string line{ std::format("보고 {}: {}\n", m_id, i) };
            std::lock_guard lock{ s_mutex };  // 출력하는 동안만 짧게 잡는다.
            std::cout << line;
        }
    }
private:
    int m_id;
    inline static std::mutex s_mutex;
};

// 3) 시간 제한 뮤텍스: 정해진 시간 안에 못 잡으면 포기한다.
std::timed_mutex g_slow;
void try_print(int id)
{
    std::unique_lock lock{ g_slow, 30ms };    // 30ms 동안 시도
    if (lock) {
        std::osyncstream{ std::cout } << "시도 " << id << ": 잡음\n";
        std::this_thread::sleep_for(100ms);   // 일부러 오래 잡고 있는다.
    } else {
        std::osyncstream{ std::cout } << "시도 " << id << ": 포기\n";
    }
}

// 4) 한 번만 초기화: 이중 검사 잠금 대신 "마법 static"을 쓴다.
const std::vector<int>& table()
{
    static const std::vector<int> t{ [] {
        std::osyncstream{ std::cout } << "표 만들기(한 번)\n";
        return std::vector<int>{ 1, 2, 3 };
    }() };
    return t;
}

int main()
{
    {
        std::jthread a{ report_sync, 1 };
        std::jthread b{ report_sync, 2 };
    }
    {
        std::jthread a{ Reporter{ 1 } };
        std::jthread b{ Reporter{ 2 } };
    }
    {
        std::jthread a{ try_print, 1 };
        std::this_thread::sleep_for(10ms);    // a가 먼저 잡게
        std::jthread b{ try_print, 2 };
    }
    {
        std::vector<std::jthread> threads;
        for (int i{ 0 }; i < 4; ++i) {
            threads.emplace_back([] { (void)table().size(); });
        }
    }
    std::println("표 크기 {}", table().size());
}
