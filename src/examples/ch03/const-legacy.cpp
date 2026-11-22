#include <cstring>
#include <print>

// 고칠 수 없는 오래된 함수라고 하자.
// text를 읽기만 하지만 매개변수에 const가 빠져 있다.
std::size_t legacyLength(char* text)
{
    return std::strlen(text);
}

// 새로 쓰는 함수: 바꾸지 않는 것은 const로 받는다.
void printLength(const char* text)
{
    // legacyLength(text);   // 컴파일 오류: const char*를 char*로 못 바꾼다.

    // legacyLength가 text를 바꾸지 않는다는 것이 확실할 때만,
    // 이 호출 한 곳에서 const를 잠시 뗀다.
    std::println("{}", legacyLength(const_cast<char*>(text)));
}

int main()
{
    printLength("Hello");
}
