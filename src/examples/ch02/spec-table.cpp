#include <print>
#include <string>
#include <vector>

struct Item
{
    std::string name;
    int count;
    double price;
};

int main()
{
    std::vector<Item> items{
        { "apple", 3, 1.5 },
        { "watermelon", 12, 23.456 },
        { "kiwi", 150, 0.8 },
    };

    std::println("{:<12}{:>6}{:>10}", "item", "qty", "price");
    std::println("{:-<28}", "");
    for (const auto& item : items) {
        std::println("{:<12}{:>6}{:>10.2f}", item.name, item.count,
                     item.price);
    }
}
