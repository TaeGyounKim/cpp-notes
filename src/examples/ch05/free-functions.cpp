#include <algorithm>
#include <print>
#include <string>
#include <vector>

class Book
{
public:
    Book(std::string title, int pageCount)
        : m_title{ title }, m_pageCount{ pageCount }
    {
    }

    const std::string& getTitle() const { return m_title; }
    int getPageCount() const { return m_pageCount; }

private:
    std::string m_title;
    int m_pageCount;
};

// 클래스에 넣지 않은 독립 함수. Book의 공개 인터페이스만으로 할 수 있는 일이다.
bool isLongerThan(const Book& book, int pageCount)
{
    return book.getPageCount() > pageCount;
}

int main()
{
    std::vector<Book> books{ { "Design Notes", 320 },
                             { "C++ Basics", 180 },
                             { "Clean Style", 240 } };

    // 표준 라이브러리의 알고리즘도 클래스의 멤버가 아니라 독립 함수다.
    std::ranges::sort(books, {}, &Book::getPageCount);

    for (const auto& book : books) {
        std::println("{:<14} {:>4}쪽 {}", book.getTitle(),
                     book.getPageCount(),
                     isLongerThan(book, 200) ? "(긴 책)" : "");
    }
}
