#include <print>
#include <string>

int main()
{
    std::string text{ "Hello\tWorld!\n" };

    // 보통의 출력: 탭과 줄바꿈이 실제로 적용된다.
    std::println("[{}]", text);

    // ? 를 붙이면 코드에 리터럴로 적을 때의 모양으로 출력된다.
    std::println("[{:?}]", text);

    // 문자열은 큰따옴표로, 문자는 작은따옴표로 감싸진다.
    std::println("{:?} {:?}", "quote\"inside", 'x');
    std::println("{:?} {:?}", '\'', '"');

    // 공백만 들어 있는지, 끝에 무엇이 붙었는지 눈으로 확인할 때 쓸모 있다.
    std::string input{ "yes \r" };
    std::println("입력: {:?}", input);
}
