#include <print>
#include <string>

// 바뀌지 않는 값에 이름을 붙인다.
const int versionMajor{ 2 };
const int versionMinor{ 1 };
const std::string productName{ "Tiny Notes" };
const double pi{ 3.141592653589793 };

int main()
{
    std::println("{} {}.{}", productName, versionMajor, versionMinor);

    const double radius{ 2.0 };
    std::println("넓이: {}", pi * radius * radius);

    // versionMajor = 3;   // 오류: const 변수는 바꿀 수 없다.
}
