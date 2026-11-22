#include <cstring>
#include <iostream>

int main()
{
    // C 스타일 문자열과 <cstring> 함수는 예전 그대로다.
    char name[]{ "abc" };
    std::cout << std::strlen(name) << ' ' << sizeof(name) << '\n';

    // 로 문자열 리터럴은 C++11에서 들어왔으므로 쓸 수 있다.
    std::cout << R"(C:\temp\notes.txt)" << '\n';
}
