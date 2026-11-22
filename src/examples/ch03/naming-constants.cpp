#include <print>
#include <utility>

// 방법 1: 네임스페이스로 나눈 상수
namespace Menu
{
    const int File{ 1 };
    const int Help{ 2 };
}

namespace Button
{
    const int Ok{ 1 };
    const int Help{ 2 };
}

// 방법 2(권장): 범위 있는 열거형. 타입이 달라 서로 섞어 쓸 수 없다.
enum class MenuId { File, Edit, Help };
enum class ButtonId { Ok, Cancel, Help };

void openMenu(MenuId id)
{
    std::println("메뉴 {} 열기", std::to_underlying(id));
}

int main()
{
    // 같은 이름 Help가 둘이지만 충돌하지 않는다.
    std::println("{} {}", Menu::Help, Button::Help);

    openMenu(MenuId::Help);
    // openMenu(ButtonId::Help);   // 컴파일 오류: 타입이 다르다.
}
