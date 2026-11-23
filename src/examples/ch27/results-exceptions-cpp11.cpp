#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <thread>

// exception_ptr, current_exception, rethrow_exception은 C++11부터 있다.
// jthread(C++20)가 없으므로 thread를 직접 join한다.
void risky(int n, std::exception_ptr& error)
{
    try {
        if (n < 0) { throw std::invalid_argument("negative"); }
        std::cout << "done " << n << '\n';
    } catch (...) {
        error = std::current_exception();
    }
}

int main()
{
    std::exception_ptr error;
    std::thread t(risky, -1, std::ref(error));
    t.join();
    try {
        if (error) { std::rethrow_exception(error); }
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
