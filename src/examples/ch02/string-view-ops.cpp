#include <print>
#include <string>
#include <string_view>

int main()
{
    std::string text{ "  hello world  " };
    std::string_view view{ text };

    // 크기는 포인터 하나와 길이 하나. 문자열이 길어도 같다.
    std::println("sizeof(string_view) = {}", sizeof(view));

    // 앞뒤를 잘라 낸다. 원본은 바뀌지 않고 "보는 범위"만 줄어든다.
    view.remove_prefix(2);
    view.remove_suffix(2);
    std::println("[{}]", view);
    std::println("[{}]", text);

    // string과 같은 읽기 전용 연산을 쓸 수 있다.
    std::println("{} {} {}", view.size(), view.starts_with("hello"),
                 view.contains("wor"));
    std::println("{}", view.substr(6));

    // string_view -> string: 직접 만들어야 한다. 이때 복사가 일어난다.
    std::string copy{ view };
    std::string joined{ copy + "!" };
    std::println("{}", joined);

    // string + string_view 는 바로 되지 않는다.
    std::string greeting{ "Say: " };
    // auto bad{ greeting + view };          // 오류
    std::string ok{ greeting + std::string{ view } };
    greeting.append(view);                   // 또는 append
    std::println("{} / {}", ok, greeting);
}
