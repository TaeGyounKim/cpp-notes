#include <print>

int main()
{
    int* price{ new int{ 1000 } };
    delete price;   // 메모리를 돌려줬다. price는 이제 매달린 포인터

    // 버그: 돌려준 메모리를 읽는다.
    std::println("{}", *price);

    // 해 볼 것: 위 줄을 지우고 아래 줄의 주석을 풀면 두 번 지우기
    // delete price;
}
