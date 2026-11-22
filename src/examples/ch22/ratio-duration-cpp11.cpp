#include <chrono>
#include <iostream>
#include <ratio>

// ratio, duration, duration_cast는 C++11부터 있다.
// 리터럴(1h)은 C++14, floor/ceil/round는 C++17, duration 출력과
// hh_mm_ss는 C++20이므로 count()와 나눗셈으로 대신한다.
int main()
{
    using sum = std::ratio_add<std::ratio<2, 6>, std::ratio<1, 6>>;
    std::cout << "sum = " << sum::num << '/' << sum::den << '\n';

    using namespace std::chrono;
    duration<int, std::ratio<60>> lap(3);
    duration<int> rest(45);
    seconds total = lap * 4 + rest * 3;
    minutes cut = duration_cast<minutes>(total);
    std::cout << total.count() << "s -> " << cut.count() << "min\n";

    seconds meeting = hours(1) + minutes(25) + seconds(30);
    long long t = meeting.count();
    std::cout << t / 3600 << "h " << t % 3600 / 60 << "min " << t % 60
              << "s\n";
}
