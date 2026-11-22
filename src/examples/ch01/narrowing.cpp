#include <print>

int main()
{
    // 작은 타입 -> 큰 타입: 잃는 값이 없으므로 형변환을 적지 않아도
    // 컴파일러가 알아서 바꿔 준다. 경고나 오류도 없다.
    short small{ 300 };
    long big{ small };
    std::println("{}", big);

    // 값을 잃는 방향 (축소 변환)
    int a = 12.87;     // 대입 문법: 소수 부분이 말없이 사라진다.
    std::println("{}", a);

    // int b{ 12.87 }; // 중괄호: 값을 잃는 변환이라 컴파일러가 막는다.
}
