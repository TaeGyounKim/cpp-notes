#include <print>

struct Product
{
    char grade;
    int id;
    int price;
};

int main()
{
    Product item;        // 필드 세 개가 한꺼번에 생긴다. 아직 값은 없다.
    item.grade = 'A';
    item.id = 1024;
    item.price = 4500;

    std::println("등급: {}", item.grade);
    std::println("번호: {}", item.id);
    std::println("가격: {}원", item.price);

    Product copy{ item };   // 필드 전체가 통째로 복사된다.
    copy.price = 5000;
    std::println("{} {}", item.price, copy.price);

    Product empty{};        // 모든 필드가 0으로 초기화된다.
    std::println("{} {}", empty.id, empty.price);
}
