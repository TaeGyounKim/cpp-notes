#include <print>

int main()
{
    // 문자열 리터럴은 읽기 전용 메모리에 놓인다. const char*로 가리킨다.
    const char* literal{ "hello" };
    // literal[1] = 'a';   // 오류: 읽기 전용인 곳을 바꾸려 했다.
    std::println("{}", literal);

    // 문자 배열을 리터럴로 초기화하면 내용이 배열로 복사된다.
    // 배열은 내 것이므로 바꿀 수 있다.
    char array[]{ "hello" };
    array[1] = 'a';
    std::println("{}", array);

    // 같은 리터럴을 두 번 쓰면 한 곳을 함께 가리킬 수도 있다.
    const char* first{ "same" };
    const char* second{ "same" };
    std::println("같은 주소인가: {}", first == second);
}
