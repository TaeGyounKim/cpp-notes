#include <print>

[[deprecated("단위가 없어 헷갈립니다. priceInWon()을 쓰세요.")]] int price()
{
    return 4500;
}

int priceInWon()
{
    return 4500;
}

int main()
{
    std::println("{}", price());        // 경고: 더 이상 권장하지 않는 함수
    std::println("{}", priceInWon());
}
