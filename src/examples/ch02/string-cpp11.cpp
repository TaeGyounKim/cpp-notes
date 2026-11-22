#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string path{ "photos/summer.png" };

    // starts_with 대신: 맨 앞에서 비교한다.
    bool starts{ path.compare(0, 7, "photos/") == 0 };

    // contains 대신: find의 결과가 npos가 아닌지 본다.
    bool contains{ path.find("summer") != std::string::npos };

    // ends_with 대신: 뒤에서부터 길이만큼 비교한다.
    std::string suffix{ ".png" };
    bool ends{ path.size() >= suffix.size() &&
               path.compare(path.size() - suffix.size(), suffix.size(),
                            suffix) == 0 };

    std::cout << std::boolalpha << starts << ' ' << contains << ' ' << ends
              << '\n';

    // "..."s 대신: std::string을 직접 만든다.
    std::vector<std::string> names{ "Kim", "Lee", "Park" };
    std::cout << names[0].size() << '\n';

    // <=> 대신: compare() 또는 <, ==, >
    std::string a{ "Hello" };
    std::string b{ "World" };
    std::cout << (a < b) << ' ' << (a.compare(b) < 0) << '\n';
}
