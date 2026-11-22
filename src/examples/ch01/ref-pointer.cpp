#include <print>

int main()
{
    // 포인터에 대한 참조: int*& 는 "int* 변수의 다른 이름"
    int* p{ nullptr };
    int*& pRef{ p };

    pRef = new int{ 5 };      // p가 새 메모리를 가리키게 된다.
    std::println("{}", *p);

    delete pRef;              // delete p; 와 같다.
    pRef = nullptr;
    std::println("{}", p == nullptr);

    // 참조의 주소는 원래 변수의 주소
    int x{ 3 };
    int& xRef{ x };
    int* xPtr{ &xRef };
    *xPtr = 100;
    std::println("{} {}", x, xPtr == &x);
}
