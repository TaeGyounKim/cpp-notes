#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// mutex, lock_guard, unique_lock, std::lock, call_once는 C++11부터 있다.
// scoped_lock과 CTAD(C++17), shared_mutex(C++17, C++14의 shared_timed_mutex)는
// 없으므로 std::lock과 adopt_lock으로 두 뮤텍스를 잡는다.
struct Account {
    std::mutex m;
    int balance;
};

void transfer(Account& from, Account& to, int amount)
{
    std::lock(from.m, to.m);                             // 교착 없이 둘 다
    std::lock_guard<std::mutex> l1(from.m, std::adopt_lock);
    std::lock_guard<std::mutex> l2(to.m, std::adopt_lock);
    from.balance -= amount;
    to.balance += amount;
}

int main()
{
    Account a, b;
    a.balance = 100;
    b.balance = 100;
    std::thread t1([&] { for (int i = 0; i < 50; ++i) { transfer(a, b, 1); } });
    std::thread t2([&] { for (int i = 0; i < 30; ++i) { transfer(b, a, 1); } });
    t1.join();
    t2.join();
    std::cout << a.balance << ' ' << b.balance << '\n';
}
