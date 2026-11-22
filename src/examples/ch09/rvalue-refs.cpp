#include <print>
#include <string>
#include <utility>

void store(std::string&& text)   // 우측값만 받는다.
{
    std::println("    store가 받음: {}", text);
}

void handle(std::string& text)    // 좌측값 참조: 이름 있는 변수
{
    std::println("  좌측값 판: {}", text);
}

void handle(std::string&& text)   // 우측값 참조: 임시 값
{
    std::println("  우측값 판: {}", text);
    // text는 이름이 있으므로 여기서는 좌측값이다.
    // store(text);                // 컴파일 오류
    store(std::move(text));        // 다시 우측값으로 바꿔 넘긴다.
}

std::string makeName() { return "센서-7"; }

int main()
{
    std::string a{ "실내 " };
    std::string b{ "온도" };

    std::println("handle(a)");
    handle(a);                  // a는 이름 있는 변수: 좌측값
    std::println("handle(a + b)");
    handle(a + b);              // a + b의 결과는 임시 값: 우측값
    std::println("handle(\"리터럴\")");
    handle("리터럴");           // 리터럴로 만든 임시 string: 우측값
    std::println("handle(std::move(b))");
    handle(std::move(b));       // move는 좌측값을 우측값 참조로 바꿀 뿐

    // 우측값 참조 변수: 임시 값의 수명이 참조의 범위만큼 늘어난다.
    std::string&& name{ makeName() };
    std::println("name: {}", name);
}
