#include <atomic>
#include <map>
#include <mutex>
#include <print>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

// 1) 스핀락: atomic_flag 하나로. 짧게만 잡을 때만 쓴다.
class Spinlock {
public:
    void lock() { while (m_flag.test_and_set()) {} }   // 잡힐 때까지 돈다.
    void unlock() { m_flag.clear(); }
private:
    std::atomic_flag m_flag;      // C++20부터 기본 생성은 "놓인" 상태
};

// 2) 읽기는 여럿이 함께, 쓰기는 혼자: shared_mutex
class PhoneBook {
public:
    void add(const std::string& name, int number)
    {
        std::unique_lock lock{ m_mutex };          // 쓰기 잠금(독점)
        m_entries[name] = number;
    }
    int find(const std::string& name) const
    {
        std::shared_lock lock{ m_mutex };          // 읽기 잠금(공유)
        auto it{ m_entries.find(name) };
        return it == m_entries.end() ? -1 : it->second;
    }
private:
    mutable std::shared_mutex m_mutex;
    std::map<std::string, int> m_entries;
};

// 3) 두 계좌 사이 이체: 두 뮤텍스를 교착 없이 한 번에 잡는다.
struct Account {
    std::mutex m;
    int balance{ 0 };
};
void transfer(Account& from, Account& to, int amount)
{
    std::scoped_lock lock{ from.m, to.m };         // 순서를 신경 쓰지 않아도 됨
    from.balance -= amount;
    to.balance += amount;
}

std::once_flag g_init;
void init_once() { std::println("공유 자원 초기화(딱 한 번)"); }

int main()
{
    Spinlock spin;
    std::vector<int> data;
    {
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 4; ++t) {
            threads.emplace_back([&, t] {
                for (int i{ 0 }; i < 100; ++i) {
                    std::lock_guard lock{ spin };  // 스핀락도 lock_guard로
                    data.push_back(t);
                }
            });
        }
    }
    std::println("스핀락으로 넣은 원소 {}", data.size());

    std::mutex m;
    int counter{ 0 };
    {
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 4; ++t) {
            threads.emplace_back([&] {
                for (int i{ 0 }; i < 1000; ++i) {
                    std::lock_guard lock{ m };     // 범위 끝에서 놓음
                    ++counter;
                }
            });
        }
    }
    std::println("뮤텍스로 보호한 counter {}", counter);

    PhoneBook book;
    {
        std::jthread writer{ [&] {
            book.add("kim", 1234);
            book.add("lee", 5678);
        } };
    }
    {
        std::jthread r1{ [&] { std::println("kim {}", book.find("kim")); } };
    }
    std::println("park {}", book.find("park"));

    Account a, b;
    a.balance = 100;
    b.balance = 100;
    {
        std::jthread t1{ [&] {
            for (int i{ 0 }; i < 50; ++i) { transfer(a, b, 1); }
        } };
        std::jthread t2{ [&] {
            for (int i{ 0 }; i < 30; ++i) { transfer(b, a, 1); }
        } };
    }
    std::println("a {} b {} 합 {}", a.balance, b.balance,
                 a.balance + b.balance);

    {
        std::vector<std::jthread> threads;
        for (int t{ 0 }; t < 3; ++t) {
            threads.emplace_back([] { std::call_once(g_init, init_once); });
        }
    }

    // unique_lock: 나중에 잠그거나, 시도만 해 볼 수 있다.
    std::unique_lock later{ m, std::defer_lock };
    std::println("잠겼나? {}", later.owns_lock());
    later.lock();
    std::println("잠겼나? {}", later.owns_lock());
}
