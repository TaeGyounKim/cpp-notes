#include <cstring>   // strlen, strcpy, strcat
#include <print>

// 문자열을 복사해 새 메모리에 담아 돌려준다.
// 돌려받은 쪽이 delete[] 해야 한다.
char* copyString(const char* text)
{
    // 글자 수 + 1: 끝을 알리는 널 문자의 자리까지 마련한다.
    char* result{ new char[std::strlen(text) + 1] };
    std::strcpy(result, text);
    return result;
}

// 두 문자열을 이어 붙인 새 문자열을 돌려준다.
char* joinStrings(const char* first, const char* second)
{
    char* result{ new char[std::strlen(first) + std::strlen(second) + 1] };
    std::strcpy(result, first);    // first를 복사
    std::strcat(result, second);   // 그 뒤에 second를 붙임
    return result;
}

int main()
{
    char* copy{ copyString("hello") };
    std::println("{} ({}글자)", copy, std::strlen(copy));

    char* joined{ joinStrings("C", "++") };
    std::println("{}", joined);

    delete[] copy;
    delete[] joined;
}
