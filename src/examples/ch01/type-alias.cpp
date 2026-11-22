#include <print>
#include <string>
#include <vector>

// 긴 타입에 짧고 뜻이 드러나는 이름을 붙인다.
using ScoreList = std::vector<int>;
using NameList = std::vector<std::string>;

// 옛 방식: typedef. 순서가 반대다. (원래 타입이 앞, 새 이름이 뒤)
typedef std::vector<double> PriceList;

int total(const ScoreList& scores)
{
    int sum{ 0 };
    for (int score : scores) {
        sum += score;
    }
    return sum;
}

int main()
{
    ScoreList scores{ 90, 75, 60 };
    std::println("{}", total(scores));

    // 별칭은 새 타입이 아니다. 원래 타입과 완전히 같은 타입이다.
    std::vector<int> plain{ 1, 2, 3 };
    scores = plain;
    std::println("{}", total(scores));

    NameList names{ "Kim", "Lee" };
    PriceList prices{ 4500.0, 3000.5 };
    std::println("{} {}", names, prices);
}
