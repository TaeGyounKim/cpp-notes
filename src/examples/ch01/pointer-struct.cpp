#include <print>

struct Product
{
    char grade;
    int id;
    int price;
};

int main()
{
    Product* item{ new Product{ 'A', 1024, 4500 } };

    // 포인터가 가리키는 구조체의 필드에 접근하는 두 가지 방법
    std::println("{}", (*item).price);   // 역참조한 뒤 점
    std::println("{}", item->price);     // 화살표 연산자. 같은 뜻

    item->price = 5000;
    std::println("{}", item->price);

    // 단락 평가: item이 널 포인터면 && 뒤는 실행되지 않는다.
    bool valid{ item != nullptr && item->price > 0 };
    std::println("{}", valid);

    delete item;
    item = nullptr;

    valid = item != nullptr && item->price > 0;
    std::println("{}", valid);
}
