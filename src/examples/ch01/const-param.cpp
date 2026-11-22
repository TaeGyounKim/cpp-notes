#include <print>
#include <string>

// 가리키는 문자열을 읽기만 하겠다는 약속
void printTitle(const std::string* title)
{
    std::println("제목: {}", *title);
    // *title = "바뀐 제목";   // 오류: const를 거쳐서는 바꿀 수 없다.
}

// 매개변수 자신을 함수 안에서 바꾸지 않겠다는 표시
int doubled(const int value)
{
    // value = 0;   // 오류
    return value * 2;
}

int main()
{
    std::string title{ "첫 번째 노트" };

    // &title의 타입은 std::string*. const std::string*로 자동 변환된다.
    printTitle(&title);

    std::println("{}", doubled(21));
}
