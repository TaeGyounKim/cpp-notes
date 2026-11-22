#include <memory>
#include <print>
#include <string>
#include <utility>
#include <vector>

// 기반 클래스: 모든 요소에 공통인 속성과 행동
class Element
{
public:
    explicit Element(int top) : m_top{ top } {}
    virtual ~Element() = default;

    int getTop() const { return m_top; }

    // 그리는 방법은 종류마다 다르다. 기본 동작만 정해 둔다.
    virtual void draw() const { std::println("{:>3}: (빈 요소)", m_top); }

private:
    int m_top;   // 문서 안에서의 세로 위치
};

// 문단은 요소이다. 그리는 방법을 바꾼다(기능 바꾸기).
class Paragraph : public Element
{
public:
    Paragraph(int top, std::string text)
        : Element{ top }, m_text{ std::move(text) }
    {
    }

    void draw() const override
    {
        std::println("{:>3}: 문단 \"{}\"", getTop(), m_text);
    }

private:
    std::string m_text;   // 속성 더하기
};

// 그림은 요소이다. 속성과 기능을 더하고, 그리는 방법을 바꾼다.
class Picture : public Element
{
public:
    Picture(int top, int width, int height)
        : Element{ top }, m_width{ width }, m_height{ height }
    {
    }

    void draw() const override
    {
        std::println("{:>3}: 그림 {}x{}", getTop(), m_width, m_height);
    }

    // 기능 더하기: 그림에만 있는 행동
    void scale(int percent)
    {
        m_width = m_width * percent / 100;
        m_height = m_height * percent / 100;
    }

private:
    int m_width;
    int m_height;
};

int main()
{
    auto picture{ std::make_unique<Picture>(30, 640, 480) };
    picture->scale(50);

    std::vector<std::unique_ptr<Element>> document;
    document.push_back(std::make_unique<Paragraph>(0, "제목"));
    document.push_back(std::move(picture));
    document.push_back(std::make_unique<Paragraph>(80, "본문"));
    document.push_back(std::make_unique<Element>(120));

    // 다형성: 종류를 묻지 않고 "그려라"라고만 한다.
    for (const auto& element : document) {
        element->draw();
    }
}
