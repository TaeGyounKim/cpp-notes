#include <chrono>
#include <future>
#include <print>
#include <stdexcept>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

long long sum_range(int from, int to)
{
    long long s{ 0 };
    for (int i{ from }; i <= to; ++i) { s += i; }
    return s;
}

int checked_div(int a, int b)
{
    if (b == 0) { throw std::invalid_argument{ "0으로 나눔" }; }
    return a / b;
}

int main()
{
    // 1) promise / future: 결과를 넣는 쪽과 꺼내는 쪽
    std::promise<int> promise;
    std::future<int> future{ promise.get_future() };   // 옮기기 전에 받는다.
    std::jthread producer{ [p = std::move(promise)]() mutable {
        std::this_thread::sleep_for(20ms);
        p.set_value(42);
    } };
    std::println("기다리는 중...");
    std::println("promise로 받은 값 {}", future.get());   // 준비될 때까지 막힘

    // 2) packaged_task: 호출 결과(값 또는 예외)를 알아서 promise에 담는다.
    std::packaged_task<long long(int, int)> task{ sum_range };
    std::future<long long> f2{ task.get_future() };
    std::jthread worker{ std::move(task), 1, 100 };
    std::println("packaged_task 1..100 합 {}", f2.get());

    // 3) async: 가장 간단하다. 정책으로 새 스레드에서 돌게 강제할 수 있다.
    auto f3{ std::async(std::launch::async, sum_range, 1, 1000) };
    // deferred: 새 스레드 없이 get()을 부를 때 이 스레드에서 실행
    auto f4{ std::async(std::launch::deferred, sum_range, 1, 10) };
    std::println("async {} / deferred {}", f3.get(), f4.get());

    // 결과가 준비됐는지 막히지 않고 확인하기
    auto slow{ std::async(std::launch::async, [] {
        std::this_thread::sleep_for(50ms);
        return 7;
    }) };
    if (slow.wait_for(0ms) == std::future_status::timeout) {
        std::println("아직 준비 안 됨: 다른 일을 할 수 있음");
    }
    std::println("결국 {}", slow.get());

    // 4) 예외도 future로 넘어온다: get()이 다시 던진다.
    auto bad{ std::async(std::launch::async, checked_div, 1, 0) };
    try {
        std::println("{}", bad.get());
    } catch (const std::exception& e) {
        std::println("future에서 받은 예외: {}", e.what());
    }

    // 5) shared_future: 여러 스레드가 같은 결과를 기다린다.
    std::promise<int> start;
    std::shared_future<int> go{ start.get_future().share() };
    std::vector<std::future<int>> results;
    for (int i{ 1 }; i <= 3; ++i) {
        results.push_back(std::async(std::launch::async,
                                     [go, i] { return go.get() * i; }));
    }
    start.set_value(10);                       // 셋을 한꺼번에 깨운다.
    std::vector<int> got;
    for (auto& r : results) { got.push_back(r.get()); }
    std::println("shared_future {}", got);
}
