#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// 스트림 반복자, 삽입 반복자, 역방향 반복자는 C++98부터,
// make_move_iterator는 C++11부터 있다. 클래스 템플릿 인수 추론(C++17)은
// 없으므로 back_inserter, inserter 같은 도우미 함수를 쓴다.
int main()
{
    std::istringstream input("7 3 9 3 5");
    std::vector<int> readings((std::istream_iterator<int>(input)),
                              std::istream_iterator<int>());

    std::copy(readings.rbegin(), readings.rend(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::set<int> unique;
    std::copy(readings.begin(), readings.end(),
              std::inserter(unique, unique.begin()));

    std::vector<std::string> names = { "A", "B" };
    std::vector<std::string> moved(std::make_move_iterator(names.begin()),
                                   std::make_move_iterator(names.end()));
    std::cout << unique.size() << ' ' << moved[0] << moved[1] << '\n';
}
