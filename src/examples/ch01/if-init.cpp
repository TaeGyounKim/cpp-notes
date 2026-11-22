#include <print>

int main()
{
    int price{ 4500 };
    int count{ 3 };

    // total은 이 if 문 안에서만 쓰는 변수
    if (int total{ price * count }; total >= 10000) {
        std::println("{}원: 무료 배송", total);
    } else {
        std::println("{}원: 배송비 3000원 추가", total);
    }

    // std::println("{}", total);   // 오류: if 문 밖에서는 total이 없다.
}
