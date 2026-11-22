#include <iostream>

int main()
{
    // C++11 모드에서는 이후 표준의 기능 검사 매크로가 정의되지 않는다.
#ifdef __cpp_range_based_for
    std::cout << "범위 기반 for: " << __cpp_range_based_for << '\n';
#endif
#ifdef __cpp_consteval
    std::cout << "consteval 있음\n";
#else
    std::cout << "consteval 없음\n";
#endif
}
