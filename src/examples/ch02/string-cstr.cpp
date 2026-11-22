#include <cstring>
#include <print>
#include <string>

int main()
{
    std::string name{ "report.txt" };

    // C 스타일 문자열을 받는 함수에 넘길 때: c_str()
    const char* cString{ name.c_str() };
    std::println("{}글자", std::strlen(cString));

    // data(): const가 아닌 string에서는 char*를 돌려준다. (C++17)
    char* raw{ name.data() };
    raw[0] = 'R';
    std::println("{}", name);

    // 주의: string이 바뀌거나 사라지면 받아 둔 포인터는 쓸 수 없다.
    // 필요할 때마다 다시 c_str()을 부를 것
}
