#include <print>

int main()
{
    int count;          // 초기화하지 않았다.
    int total{ 7 };     // 7로 초기화했다.

    std::println("total = {}", total);
    std::println("count = {}", count);
}
