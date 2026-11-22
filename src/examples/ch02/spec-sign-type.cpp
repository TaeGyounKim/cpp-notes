#include <print>

int main()
{
    int number{ 42 };

    // 부호
    std::println("|{:+}|{:+}|", number, -number);   // 항상 부호 표시
    std::println("|{: }|{: }|", number, -number);   // 양수는 빈칸
    std::println("|{:-}|{:-}|", number, -number);   // 음수만 표시 (기본)

    // 타입: 정수를 다른 진법으로
    std::println("{:d} {:b} {:o} {:x} {:X}", number, number, number,
                 number, number);

    // #: 진법 접두어를 붙인다.
    std::println("{:#b} {:#o} {:#x} {:#X}", number, number, number, number);

    // bool과 char
    std::println("{} {:d}", true, true);
    std::println("{} {:d}", 'A', 'A');

    // 포인터: void* 만 형식화할 수 있다.
    std::println("{}", static_cast<void*>(nullptr));
}
