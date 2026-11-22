#include <print>

int main()
{
    // 자유 저장소에 int 하나를 만들고, 그 주소를 p에 담는다.
    int* p{ new int{ 5 } };
    std::println("{}", *p);

    *p = 6;
    std::println("{}", *p);

    // 다 썼으면 직접 돌려줘야 한다.
    delete p;
    p = nullptr;   // 돌려준 메모리를 실수로 다시 쓰지 않도록 비워 둔다.

    if (p == nullptr) {
        std::println("p는 이제 아무것도 가리키지 않는다.");
    }
}
