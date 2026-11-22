#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Element
{
public:
    explicit Element(int top) : m_top{ top } {}
    virtual ~Element() = default;

    int getTop() const { return m_top; }
    virtual void draw() const { std::cout << m_top << ": (빈 요소)\n"; }

private:
    int m_top;
};

class Paragraph : public Element
{
public:
    Paragraph(int top, std::string text)
        : Element{ top }, m_text{ std::move(text) }
    {
    }

    void draw() const override
    {
        std::cout << getTop() << ": 문단 \"" << m_text << "\"\n";
    }

private:
    std::string m_text;
};

int main()
{
    std::vector<std::unique_ptr<Element>> document;

    // std::make_unique(C++14) 대신 new로 만든 포인터를 unique_ptr에 맡긴다.
    document.push_back(std::unique_ptr<Element>(new Paragraph(0, "제목")));
    document.push_back(std::unique_ptr<Element>(new Element(120)));

    for (const auto& element : document) {
        element->draw();
    }
}
