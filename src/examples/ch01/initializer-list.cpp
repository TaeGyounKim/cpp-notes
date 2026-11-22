#include <initializer_list>
#include <print>

// 정수를 몇 개든 받아 합을 돌려준다.
int sum(std::initializer_list<int> values)
{
    int total{ 0 };
    for (int value : values) {
        total += value;
    }
    return total;
}

int main()
{
    std::println("{}", sum({ 1, 2, 3 }));
    std::println("{}", sum({ 10, 20, 30, 40, 50, 60 }));
    std::println("{}", sum({}));

    // std::println("{}", sum({ 1, 2, 3.0 }));   // 오류: double은 받을 수 없다.
}
