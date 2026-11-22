#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

// 시계, time_point, time_point_cast는 C++11부터 있다.
// 시각 출력(C++20)이 없으므로 time_t와 std::gmtime, strftime을 쓴다.
int main()
{
    using namespace std::chrono;

    std::time_t t = system_clock::to_time_t(system_clock::now());
    char buf[64];
    std::strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", std::gmtime(&t));
    std::cout << "UTC " << buf << '\n';

    steady_clock::time_point start = steady_clock::now();
    double acc = 0;
    for (int i = 0; i < 2000000; ++i) { acc += std::sqrt(i) * std::sin(i); }
    duration<double, std::milli> ms = steady_clock::now() - start;
    std::cout << "acc " << acc << ", " << ms.count() << "ms\n";

    time_point<steady_clock, milliseconds> odd(milliseconds(95000));
    time_point<steady_clock, minutes> coarse = time_point_cast<minutes>(odd);
    std::cout << coarse.time_since_epoch().count() << "min\n";
}
