#include <iostream>

struct Product
{
    char grade;
    int id;
    int price;
};

int main()
{
    // 포인터, new, delete, nullptr 모두 C++11에서 그대로 쓴다.
    int score{ 8 };
    int* p{ &score };
    *p = 10;
    std::cout << score << '\n';

    Product* item{ new Product{ 'A', 1024, 4500 } };
    std::cout << item->price << '\n';
    delete item;
    item = nullptr;

    int* numbers{ new int[3]{} };
    numbers[1] = 2;
    std::cout << numbers[0] << ' ' << numbers[1] << '\n';
    delete[] numbers;
    numbers = nullptr;
}
