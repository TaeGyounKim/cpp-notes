#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

// future, promise, packaged_task, async, shared_future는 C++11부터 있다.
// 람다의 초기화 캡처(C++14)가 없으므로 promise를 스레드 인수로 옮긴다.
int checked_div(int a, int b)
{
    if (b == 0) { throw std::invalid_argument("divide by zero"); }
    return a / b;
}

void produce(std::promise<int> p) { p.set_value(42); }

int main()
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread producer(produce, std::move(promise));
    std::cout << future.get() << '\n';
    producer.join();

    std::future<int> bad = std::async(std::launch::async, checked_div, 1, 0);
    try {
        bad.get();
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
