#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <print>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    // istream_iterator: 표준 입력에서 정수를 끝까지 읽는다.
    std::istream_iterator<int> first{ std::cin };
    std::istream_iterator<int> last;              // 기본 생성 = 끝
    std::vector<int> readings(first, last);
    std::println("읽은 값 {}, 합 {}", readings,
                 std::accumulate(readings.begin(), readings.end(), 0));

    // ostream_iterator: 알고리즘의 출력 대상을 스트림으로
    std::copy(readings.begin(), readings.end(),
              std::ostream_iterator<int>{ std::cout, " | " });
    std::cout << '\n';

    // istreambuf_iterator: 스트림의 글자를 그대로(공백 포함) 읽는다.
    std::istringstream text{ "온도 21.5\n습도 40" };
    std::string all{ std::istreambuf_iterator<char>{ text },
                     std::istreambuf_iterator<char>{} };
    std::println("{}바이트를 통째로 읽음(공백, 줄바꿈 포함)", all.size());

    // 삽입 반복자: 대상 컨테이너의 크기를 미리 맞추지 않아도 된다.
    std::vector<int> big;
    std::copy_if(readings.begin(), readings.end(), std::back_inserter(big),
                 [](int x) { return x >= 5; });
    std::set<int> unique;
    std::copy(readings.begin(), readings.end(),
              std::inserter(unique, unique.begin()));
    std::println("5 이상 {}, 중복 없이 {}", big, unique);
}
