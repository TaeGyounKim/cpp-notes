#include <print>
#include <string>
#include <utility>

class Image
{
public:
    explicit Image(std::string file) : m_file{ std::move(file) } {}
    void draw() const { std::println("그림 '{}' 그리기", m_file); }

private:
    std::string m_file;
};

class Button
{
public:
    void draw() const { std::println("버튼 테두리 그리기"); }
    void click() const { std::println("눌림"); }
};

// 그림 버튼은 그림이기도 하고 버튼이기도 하다?
class ImageButton : public Image, public Button
{
public:
    explicit ImageButton(std::string file) : Image{ std::move(file) } {}
};

int main()
{
    ImageButton save{ "save.png" };
    save.click();   // Button에만 있으므로 문제없다.

    // save.draw();   // 컴파일 오류: Image::draw인지 Button::draw인지 모호하다.

    // 어느 쪽인지 직접 밝혀야 한다.
    save.Image::draw();
    save.Button::draw();
}
