#include <cstring>
#include <print>

int main()
{
    char array[]{ "abcdef" };          // 문자 배열
    const char* pointer{ "abcdef" };   // 문자열 리터럴을 가리키는 포인터

    // 배열: sizeof는 널 문자까지 포함한 전체 바이트 수
    std::println("sizeof(array)   = {}", sizeof(array));
    std::println("strlen(array)   = {}", std::strlen(array));

    // 포인터: sizeof는 포인터 자신의 크기. 문자열의 길이와 관계가 없다.
    std::println("sizeof(pointer) = {}", sizeof(pointer));
    std::println("strlen(pointer) = {}", std::strlen(pointer));
}
