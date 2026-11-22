#include <iostream>

struct Product
{
    char grade;
    int id;
    int price;
};

int main()
{
    Product item{};
    item.grade = 'A';
    item.id = 1024;
    item.price = 4500;

    std::cout << item.grade << ' ' << item.id << ' ' << item.price << '\n';
}
