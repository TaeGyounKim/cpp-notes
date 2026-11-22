#include <print>

// 선언: 이름, 매개변수, 반환 타입만 알린다. 본문은 없다.
void printReceipt(int price, char grade);
int calculateTotal(int price, int count);

int main()
{
    printReceipt(4500, 'A');

    int count{ 3 };
    int total{ calculateTotal(4500, count) };
    std::println("합계: {}원", total);
}

// 정의: 실제로 실행되는 코드
void printReceipt(int price, char grade)
{
    std::println("가격: {}원", price);
    std::println("등급: {}", grade);
}

int calculateTotal(int price, int count)
{
    return price * count;
}
