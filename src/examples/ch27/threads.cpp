#include <chrono>
#include <functional>
#include <print>
#include <stop_token>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

// 1) 함수: 인수를 몇 개든 받는다. 인수는 스레드 안으로 "복사"된다.
void count_up(int id, int times)
{
    for (int i{ 1 }; i <= times; ++i) { std::println("함수 {}: {}", id, i); }
}

// 2) 함수 객체: 데이터 멤버로 상태를 가질 수 있다.
struct Countdown {
    int from;
    void operator()() const
    {
        for (int i{ from }; i > 0; --i) { std::println("객체: {}", i); }
    }
};

// 3) 멤버 함수: 특정 객체의 멤버를 다른 스레드에서 부른다.
class Job {
public:
    explicit Job(std::string name) : m_name{ std::move(name) } {}
    void run(int n) const { std::println("{} 처리 {}건", m_name, n); }
private:
    std::string m_name;
};

// thread_local: 스레드마다 따로 있다. shared는 모두 하나를 함께 쓴다.
int shared{ 0 };
thread_local int mine{ 0 };
void touch(int id)
{
    std::println("스레드 {}: shared={}, mine={}", id, shared, mine);
    ++shared;
    ++mine;
}

// 협조적 취소: stop_token을 첫 매개변수로 받아 스스로 확인한다.
void worker(std::stop_token token, int id)
{
    while (!token.stop_requested()) {    // 멈추라는 요청이 올 때까지 일한다.
        std::this_thread::sleep_for(20ms);
    }
    std::println("작업자 {}: 멈춤 요청을 받고 끝냄", id);
}

int main()
{
    std::thread t1{ count_up, 1, 2 };
    t1.join();                              // 끝날 때까지 기다린다.

    std::thread t2{ Countdown{ 2 } };
    t2.join();

    int total{ 0 };
    std::thread t3{ [&total] { total = 42; } };   // 람다: 참조 캡처
    t3.join();                              // join 뒤에 읽어야 안전
    std::println("람다 결과 {}", total);

    Job job{ "주문" };
    std::thread t4{ &Job::run, &job, 3 };   // 멤버 함수 + 객체 + 인수
    t4.join();

    std::thread a{ touch, 1 };
    a.join();
    std::thread b{ touch, 2 };
    b.join();

    int counter{ 0 };
    // 참조로 넘기려면 std::ref. 그냥 넘기면 복사본을 고친다.
    std::thread t5{ [](int& c) { c += 5; }, std::ref(counter) };
    t5.join();
    std::println("ref로 넘긴 counter {}", counter);

    {
        std::jthread w{ worker, 7 };        // 소멸자가 멈춤 요청 + join
        std::this_thread::sleep_for(250ms);
        std::println("main: 블록 끝");
    }
    std::println("main 끝");
}
