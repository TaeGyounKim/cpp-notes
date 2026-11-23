#include <exception>
#include <functional>
#include <print>
#include <stdexcept>
#include <thread>
#include <vector>

// 결과를 데이터 멤버에 담는 함수 객체
class Summer {
public:
    explicit Summer(std::vector<int> data) : m_data{ std::move(data) } {}
    void operator()()
    {
        for (int v : m_data) { m_sum += v; }
    }
    long long sum() const { return m_sum; }
private:
    std::vector<int> m_data;
    long long m_sum{ 0 };
};

// 스레드 안에서 던져진 예외는 그 스레드 안에서 잡아야 한다.
// 잡은 예외를 exception_ptr에 담아 밖으로 넘긴다.
void risky(int n, std::exception_ptr& error)
{
    try {
        if (n < 0) { throw std::invalid_argument{ "음수는 처리할 수 없음" }; }
        std::println("작업 {} 완료", n);
    } catch (...) {
        error = std::current_exception();   // 지금 처리 중인 예외를 잡아 둔다.
    }
}

void run_in_thread(int n)
{
    std::exception_ptr error;               // 처음에는 null
    std::jthread t{ risky, n, std::ref(error) };
    t.join();
    if (error) {
        std::println("메인: 스레드에서 예외를 받아 다시 던짐");
        std::rethrow_exception(error);      // 이 스레드에서 다시 던진다.
    }
}

int main()
{
    Summer s{ { 1, 2, 3, 4 } };
    // ref가 없으면 복사본에 결과가 쌓인다.
    std::jthread j1{ std::ref(s) };
    j1.join();
    std::println("합 {}", s.sum());

    Summer copy_target{ { 10, 20 } };
    std::jthread j2{ copy_target };         // 복사본에서 실행
    j2.join();
    std::println("ref 없이: {}", copy_target.sum());

    for (int n : { 3, -1 }) {
        try {
            run_in_thread(n);
        } catch (const std::exception& e) {
            std::println("main에서 잡음: {}", e.what());
        }
    }

    // make_exception_ptr: 예외 객체에서 바로 exception_ptr를 만든다.
    auto p{ std::make_exception_ptr(std::runtime_error{ "직접 만든 예외" }) };
    try {
        std::rethrow_exception(p);
    } catch (const std::runtime_error& e) {
        std::println("{}", e.what());
    }
}
