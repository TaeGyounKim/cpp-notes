#include <iostream>
#include <map>
#include <string>
#include <utility>

// 구조적 바인딩·insert_or_assign·try_emplace·extract/merge(C++17),
// contains(C++20)가 없으므로 .first/.second, find, count, 복사 후 erase를 쓴다.
int main()
{
    std::map<std::string, int> stock = { { "사과", 3 }, { "배", 7 } };

    std::pair<std::map<std::string, int>::iterator, bool> result =
        stock.insert(std::make_pair("사과", 10));
    if (!result.second) {
        std::cout << "사과는 이미 있음: " << result.first->second << '\n';
        result.first->second = 10;              // insert_or_assign 대신
    }

    stock["귤"] = 4;
    if (stock.find("감") == stock.end()) {      // try_emplace 대신
        stock.emplace("감", 2);
    }

    for (const auto& p : stock) {
        std::cout << p.first << ':' << p.second << ' ';
    }
    std::cout << '\n' << stock.count("귤") << ' ' << stock.at("감") << '\n';

    std::map<std::string, int> sold;            // extract 대신 복사 후 지움
    auto it = stock.find("배");
    sold.insert(*it);
    stock.erase(it);
    std::cout << stock.size() << ' ' << sold.size() << '\n';
}
