#include <print>

int main()
{
    int value{ 123 };

    auto p{ &value };     // int*
    auto* q{ &value };    // int*. 포인터라는 것이 드러난다.
    std::println("{} {}", *p, *q);

    // const와 함께 쓸 때는 결과가 달라진다.
    const auto p1{ &value };    // int* const: 포인터가 const
    *p1 = 1;                    // 가리키는 값은 바꿀 수 있다.

    const auto* p2{ &value };   // const int*: 가리키는 값이 const
    // *p2 = 2;                 // 오류
    p2 = nullptr;               // 포인터는 바꿀 수 있다.

    std::println("{} {}", value, p2 == nullptr);
}
