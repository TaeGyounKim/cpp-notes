#include <print>

enum Fruit { Apple, Banana };
enum Animal { Cat, Dog };

int main()
{
    Fruit fruit{ Banana };   // Fruit:: 없이 쓴다.

    int n{ fruit };          // 정수로 자동 변환된다.
    std::println("{}", n);

    // 과일과 동물이 같은지 비교한다? 뜻이 없지만 컴파일된다.
    std::println("{}", fruit == Dog);
}
