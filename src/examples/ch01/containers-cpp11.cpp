#include <array>
#include <iostream>
#include <tuple>     // std::tie
#include <utility>
#include <vector>

// std::optional 대신: 약속한 특별한 값(-1)으로 "없음"을 나타낸다.
int findDiscount(char grade)
{
    if (grade == 'A') { return 20; }
    if (grade == 'B') { return 10; }
    return -1;
}

int main()
{
    // 꺾쇠괄호 생략(CTAD)이 없으므로 타입을 모두 적는다.
    std::array<int, 3> scores{ 90, 75, 60 };
    std::vector<int> numbers{ 11, 22 };
    numbers.push_back(33);
    std::pair<int, char> item{ 4500, 'A' };

    std::cout << scores.size() << ' ' << numbers.size() << '\n';

    // 구조적 바인딩 대신: first, second를 직접 쓰거나 std::tie
    int price{};
    char grade{};
    std::tie(price, grade) = item;
    std::cout << price << ' ' << grade << '\n';

    int discount{ findDiscount('Z') };
    if (discount == -1) {
        std::cout << "no discount\n";
    }
}
