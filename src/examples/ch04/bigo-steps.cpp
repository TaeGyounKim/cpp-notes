#include <print>

// 입력 크기 n에 대해 각 알고리즘이 몇 "걸음"을 걷는지 센다.

// O(1): n과 상관없이 한 걸음
long long constantSteps(long long)
{
    return 1;
}

// O(log n): 한 걸음마다 남은 양이 절반이 된다.
long long logarithmicSteps(long long n)
{
    long long steps{ 0 };
    while (n > 1) {
        n /= 2;
        ++steps;
    }
    return steps;
}

// O(n): 원소마다 한 걸음
long long linearSteps(long long n)
{
    long long steps{ 0 };
    for (long long i{ 0 }; i < n; ++i) {
        ++steps;
    }
    return steps;
}

// O(n log n): 원소마다 log n 걸음
long long linearLogarithmicSteps(long long n)
{
    return n * logarithmicSteps(n);
}

// O(n²): 원소마다 다시 모든 원소를 한 번씩
long long quadraticSteps(long long n)
{
    long long steps{ 0 };
    for (long long i{ 0 }; i < n; ++i) {
        for (long long j{ 0 }; j < n; ++j) {
            ++steps;
        }
    }
    return steps;
}

int main()
{
    std::println("{:>6} {:>5} {:>9} {:>7} {:>11} {:>11}", "n", "O(1)",
                 "O(log n)", "O(n)", "O(n log n)", "O(n²)");
    for (long long n : { 10, 100, 1'000, 10'000 }) {
        std::println("{:>6} {:>5} {:>9} {:>7} {:>11} {:>11}", n,
                     constantSteps(n), logarithmicSteps(n), linearSteps(n),
                     linearLogarithmicSteps(n), quadraticSteps(n));
    }
}
