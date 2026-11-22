#include <print>
#include <string>
#include <utility>

// 고칠 수 없는 외부 라이브러리의 함수라고 하자.
// 받은 문자열을 바꾸지 않는데도 매개변수에 const가 빠져 있다.
void legacyPrint(char* text)
{
    std::println("{}", text);
}

void show(const char* text)
{
    // legacyPrint(text);                  // 오류: const를 뗄 수 없다.
    legacyPrint(const_cast<char*>(text));  // const를 일부러 떼어 낸다.
}

int main()
{
    show("legacy");

    // 반대로 const를 붙이는 쪽: std::as_const (C++17)
    std::string name{ "C++" };
    const std::string& view{ std::as_const(name) };
    std::println("{}", view);
}
