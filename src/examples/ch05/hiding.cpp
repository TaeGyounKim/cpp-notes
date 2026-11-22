#include <print>

class Element
{
public:
    int width{ 100 };
    void printWidth() const { std::println("Element가 보는 width: {}", width); }
};

// 이름이 같은 데이터 멤버를 또 선언했다. 바꾼 것이 아니라 하나 더 생겼다.
class Picture : public Element
{
public:
    int width{ 640 };   // Element::width를 가린다.
};

int main()
{
    Picture picture;
    std::println("Picture의 width: {}", picture.width);
    picture.printWidth();   // 기반 클래스의 함수는 자기 width를 본다.

    std::println("sizeof(Element) = {}, sizeof(Picture) = {}",
                 sizeof(Element), sizeof(Picture));
}
