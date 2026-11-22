#include <print>

int main()
{
    int score{ 8 };

    // &score: score가 놓인 메모리 주소. 그 주소를 포인터 p에 담는다.
    int* p{ &score };

    std::println("score의 값: {}", score);
    std::println("p가 가리키는 값: {}", *p);

    // *p = ...: p가 가리키는 곳의 값을 바꾼다. 즉 score가 바뀐다.
    *p = 10;
    std::println("score의 값: {}", score);

    // 주소 자체도 출력해 볼 수 있다. 실행할 때마다 달라질 수 있다.
    std::println("p에 든 주소: {}", static_cast<void*>(p));

    // 아직 가리킬 곳이 없으면 nullptr로 초기화한다.
    int* nothing{ nullptr };
    if (!nothing) {
        std::println("nothing은 널 포인터");
    }
}
