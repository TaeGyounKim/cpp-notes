#include <print>

// 반환값을 쓰지 않고 버리면 컴파일러가 경고한다.
[[nodiscard]] int saveFile()
{
    return -1;   // 실패했다는 뜻의 오류 코드라고 하자.
}

// 이유를 문자열로 적으면 경고 메시지에 함께 나온다. (C++20)
[[nodiscard("연결에 실패했을 수 있습니다. 결과를 확인하세요.")]] bool connect()
{
    return false;
}

int main()
{
    saveFile();    // 경고: 반환값을 버렸다.
    connect();     // 경고: 이유도 함께 나온다.

    int result{ saveFile() };   // 반환값을 받았으므로 경고 없음
    std::println("{}", result);
}
