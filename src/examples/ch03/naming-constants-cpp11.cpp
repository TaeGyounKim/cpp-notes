#include <iostream>

enum class MenuId { File, Edit, Help };
enum class ButtonId { Ok, Cancel, Help };

void openMenu(MenuId id)
{
    // std::to_underlying(C++23) 대신 static_cast로 정수로 바꾼다.
    std::cout << "메뉴 " << static_cast<int>(id) << " 열기\n";
}

int main()
{
    openMenu(MenuId::Help);
}
