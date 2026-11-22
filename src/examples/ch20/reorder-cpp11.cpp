#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// sample(C++17)과 shift_left/right(C++20)가 없으므로 shuffle 뒤 앞쪽을 쓰고,
// 밀기는 erase로 대신한다. unique, reverse, for_each는 C++98부터 있다.
struct Sum
{
    int total = 0;
    void operator()(int v) { total += v; }
};

void show(const std::vector<int>& v)
{
    for (int x : v) { std::cout << x << ' '; }
    std::cout << '\n';
}

int main()
{
    std::vector<int> log = { 1, 1, 2, 2, 2, 3, 1, 1 };
    log.erase(std::unique(log.begin(), log.end()), log.end());
    show(log);

    std::vector<int> deck = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::mt19937 engine(42);
    std::shuffle(deck.begin(), deck.end(), engine);   // shuffle은 C++11
    std::vector<int> picked(deck.begin(), deck.begin() + 3);
    show(picked);

    std::vector<int> queue = { 11, 22, 33, 44, 55 };
    queue.erase(queue.begin(), queue.begin() + 2);    // shift_left 2 대신
    show(queue);

    Sum s = std::for_each(queue.begin(), queue.end(), Sum());
    std::cout << s.total << '\n';
}
