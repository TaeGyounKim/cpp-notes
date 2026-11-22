#include <print>
#include <string>

// 복사하지 않고 받되, 바꾸지는 않겠다는 약속
void printTitle(const std::string& title)
{
    std::println("제목: {} ({}글자)", title, title.size());
}

int main()
{
    std::string title{ "Modern C++" };

    printTitle(title);       // 복사가 일어나지 않는다.
    printTitle("Hello");     // 리터럴도 받을 수 있다.
}
