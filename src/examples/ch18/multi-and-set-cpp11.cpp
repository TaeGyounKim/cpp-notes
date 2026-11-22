#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

// 구조적 바인딩(C++17), contains(C++20), 범위(C++20/23)가 없으므로
// equal_range의 결과를 .first/.second로 쓰고 count로 확인한다.
int main()
{
    std::multimap<std::string, std::string> schedule = {
        { "월", "필터 교체" }, { "화", "점검" }, { "월", "배터리 확인" } };
    schedule.insert(std::make_pair("월", "청소"));

    typedef std::multimap<std::string, std::string>::iterator Iter;
    std::pair<Iter, Iter> range = schedule.equal_range("월");
    std::vector<std::string> mondays;
    for (Iter it = range.first; it != range.second; ++it) {
        mondays.push_back(it->second);
    }
    std::cout << mondays.size() << ' ' << mondays.front() << '\n';

    std::set<std::string> allowed = { "민수", "지은" };
    allowed.erase("지은");
    std::multiset<int> ratings = { 5, 3, 5, 4, 5 };
    std::cout << allowed.count("지은") << ' ' << ratings.count(5) << '\n';
}
