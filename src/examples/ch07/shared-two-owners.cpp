#include <cstdio>
#include <memory>
#include <print>

int main()
{
    int* raw{ new int{ 7 } };

    // 버그: 같은 맨 포인터로 shared_ptr를 따로 두 개 만들었다.
    // 둘은 서로의 존재를 모른다. 참조 횟수도 각자 1이다.
    std::shared_ptr<int> first{ raw };
    std::shared_ptr<int> second{ raw };
    // stderr로 출력: 버퍼에 머물지 않아, 뒤에서 프로그램이 멈춰도 보인다.
    std::println(stderr, "{} {}", first.use_count(), second.use_count());
}   // 둘 다 "내가 마지막"이라 생각하고 지운다: 두 번 지우기
