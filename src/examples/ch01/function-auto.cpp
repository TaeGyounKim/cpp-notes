#include <print>

// 반환 타입을 auto로 적으면 return 뒤의 식에서 타입을 알아낸다.
auto calculateTotal(int price, int count)
{
    // __func__ 에는 지금 실행 중인 함수의 이름이 들어 있다.
    std::println("{} 함수에 들어옴", __func__);
    return price * count;      // int * int 이므로 반환 타입은 int
}

auto half(int value)
{
    return value / 2.0;        // int / double 이므로 반환 타입은 double
}

int main()
{
    std::println("{}", calculateTotal(4500, 3));
    std::println("{}", half(7));
}
