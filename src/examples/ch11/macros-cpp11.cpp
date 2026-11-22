#include <iostream>

#define SQUARE_GOOD(x) ((x) * (x))

// constexpr 함수(C++11)는 본문이 return 문 하나여야 한다.
constexpr int square(int x) { return x * x; }

int main()
{
    std::cout << SQUARE_GOOD(2 + 3) << ' ' << square(2 + 3) << '\n';
#if __cplusplus >= 201103L
    std::cout << "C++11 이상\n";
#endif
}
