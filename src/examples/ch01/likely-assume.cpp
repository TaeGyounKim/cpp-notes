#include <print>

int checkStock(int stock)
{
    // 재고가 없는 경우는 드물다고 컴파일러에 알려 준다.
    if (stock == 0) [[unlikely]] {
        return -1;
    } else {
        return stock;
    }
}

int divideBy32(int value)
{
    // value가 음수가 아니라고 가정해도 된다고 알려 준다. (C++23)
    // 확인하는 코드가 아니다. 가정이 틀리면 무슨 일이 생길지 알 수 없다.
    [[assume(value >= 0)]];
    return value / 32;
}

int main()
{
    std::println("{}", checkStock(12));
    std::println("{}", divideBy32(640));
}
