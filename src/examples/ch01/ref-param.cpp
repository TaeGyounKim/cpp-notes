#include <print>

// 값으로 받기: n은 복사본
void addOneCopy(int n)
{
    n++;
    std::println("  addOneCopy 안의 n: {}", n);
}

// 참조로 받기: n은 호출한 쪽 변수의 다른 이름
void addOneRef(int& n)
{
    n++;
    std::println("  addOneRef 안의 n: {}", n);
}

void swapValues(int& first, int& second)
{
    int temp{ first };
    first = second;
    second = temp;
}

int main()
{
    int count{ 7 };

    addOneCopy(count);
    std::println("{}", count);   // 그대로 7

    addOneRef(count);            // 호출하는 문법은 똑같다.
    std::println("{}", count);   // 8

    int a{ 5 };
    int b{ 6 };
    swapValues(a, b);
    std::println("{} {}", a, b);

    // 포인터를 가지고 있을 때는 역참조해서 넘긴다.
    int* pa{ &a };
    int* pb{ &b };
    swapValues(*pa, *pb);
    std::println("{} {}", a, b);

    // addOneRef(3);   // 오류: 리터럴에는 const가 아닌 참조를 붙일 수 없다.
}
