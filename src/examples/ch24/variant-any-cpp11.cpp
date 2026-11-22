#include <iostream>
#include <string>
#include <vector>

// variant와 any는 C++17부터다. 그 이전에는 "무엇이 들어 있는지"를 나타내는
// 태그와 값을 함께 두는 구조체를 직접 만든다(외부 라이브러리도 있다).
// 이 방식은 잘못된 태그로 읽어도 컴파일러가 막아 주지 않는다.
struct Setting {
    enum class Kind { Int, Double, String };
    Kind kind;
    int i;
    double d;
    std::string s;
};

Setting makeInt(int v) { return Setting{ Setting::Kind::Int, v, 0, "" }; }
Setting makeText(std::string v)
{
    return Setting{ Setting::Kind::String, 0, 0, v };
}

int main()
{
    std::vector<Setting> all = { makeInt(3), makeText("ko") };
    for (const Setting& x : all) {
        switch (x.kind) {
        case Setting::Kind::Int:
            std::cout << "int " << x.i << '\n';
            break;
        case Setting::Kind::Double:
            std::cout << "double " << x.d << '\n';
            break;
        case Setting::Kind::String:
            std::cout << "text " << x.s << '\n';
            break;
        }
    }
}
