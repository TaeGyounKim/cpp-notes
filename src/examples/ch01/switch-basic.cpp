#include <print>

int main()
{
    int button{ 2 };

    switch (button) {
        case 1:
            std::println("콜라");
            break;
        case 2:
            std::println("사이다");
            break;
        case 3:
            std::println("물");
            break;
        default:
            std::println("없는 버튼");
            break;
    }
}
