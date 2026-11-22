#include <print>

int main()
{
    int first{ 10 };
    int second{ 20 };

    // 1. 가리키는 값이 const: 값은 못 바꾸고, 가리키는 곳은 바꿀 수 있다.
    const int* a{ &first };
    // *a = 11;        // 오류
    a = &second;       // 가능
    std::println("{}", *a);

    // 2. 포인터 자신이 const: 값은 바꿀 수 있고, 가리키는 곳은 못 바꾼다.
    int* const b{ &first };
    *b = 11;           // 가능
    // b = &second;    // 오류
    std::println("{}", *b);

    // 3. 둘 다 const: 아무것도 바꿀 수 없다.
    const int* const c{ &first };
    // *c = 12;        // 오류
    // c = &second;    // 오류
    std::println("{}", *c);
}
