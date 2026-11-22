#include <print>

struct Product
{
    char grade;
    int id;
    int stock;
    int price{ 3000 };   // 기본값
};

void show(Product p)
{
    std::println("{} {} {} {}", p.grade, p.id, p.stock, p.price);
}

int main()
{
    // 순서대로 나열: 어느 값이 어느 필드인지 코드만 봐서는 알기 어렵다.
    Product a{ 'A', 1024, 50, 4500 };
    show(a);

    // 지정 초기화: 필드 이름을 적는다.
    Product b{
        .grade = 'A',
        .id = 1024,
        .stock = 50,
        .price = 4500,
    };
    show(b);

    // 건너뛴 필드: 기본값이 있으면 그 값(price), 없으면 0(stock)
    Product c{
        .grade = 'B',
        .id = 2048,
    };
    show(c);
}
