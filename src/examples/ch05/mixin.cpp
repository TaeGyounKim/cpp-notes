#include <print>
#include <string>
#include <utility>

// 기반 클래스: 화면에 그려지는 것
class Image
{
public:
    explicit Image(std::string file) : m_file{ std::move(file) } {}
    virtual ~Image() = default;
    const std::string& getFile() const { return m_file; }

private:
    std::string m_file;
};

// 믹스인: "~할 수 있다"를 하나씩 덧붙인다.
class Clickable
{
public:
    void click() { ++m_clickCount; }
    int getClickCount() const { return m_clickCount; }

private:
    int m_clickCount{ 0 };
};

class Draggable
{
public:
    void dragTo(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }

private:
    int m_x{ 0 };
    int m_y{ 0 };
};

// 폴더 아이콘은 그림이다(is-a). 누를 수 있고 끌 수 있다(믹스인).
class FolderIcon : public Image, public Clickable, public Draggable
{
public:
    using Image::Image;
};

// 사진 미리보기는 그림이고, 누를 수만 있다.
class Thumbnail : public Image, public Clickable
{
public:
    using Image::Image;
};

int main()
{
    FolderIcon folder{ "folder.png" };
    folder.click();
    folder.click();
    folder.dragTo(120, 40);
    std::println("{}: {}번 눌림, 위치 ({}, {})", folder.getFile(),
                 folder.getClickCount(), folder.getX(), folder.getY());

    Thumbnail photo{ "cat.jpg" };
    photo.click();
    std::println("{}: {}번 눌림", photo.getFile(), photo.getClickCount());
    // photo.dragTo(0, 0);   // 컴파일 오류: Draggable을 섞지 않았다.
}
