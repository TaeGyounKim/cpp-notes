#include <iostream>

enum class CupSize { Small, Medium, Large };
enum class Door { Open, Closed, Unknown };

int main()
{
    CupSize size{ CupSize::Medium };

    // std::to_underlying 대신 static_cast
    std::cout << static_cast<int>(size) << '\n';

    // using enum이 없으므로 항상 Door:: 를 붙인다.
    Door door{ Door::Closed };
    std::cout << static_cast<int>(door) << '\n';
}
