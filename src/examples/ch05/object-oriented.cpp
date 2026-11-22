#include <print>
#include <string>
#include <utility>
#include <vector>

// 객체 지향 방식: "어떤 대상들을 다루는가"에서 출발한다.
// 데이터(속성)와 그것을 다루는 코드(행동)가 한 클래스에 있다.

class Book
{
public:
    explicit Book(std::string title) : m_title{ std::move(title) } {}

    // 속성을 읽는 창구
    const std::string& getTitle() const { return m_title; }
    bool isOnLoan() const { return m_isOnLoan; }

    // 행동: 책은 스스로 "빌려질 수 있는지"를 안다.
    bool checkOut()
    {
        if (m_isOnLoan) {
            return false;
        }
        m_isOnLoan = true;
        return true;
    }

private:
    std::string m_title;
    bool m_isOnLoan{ false };
};

// 책의 모음. 책이라는 더 작은 구성 요소로 이루어진다.
class Library
{
public:
    void add(Book book) { m_books.push_back(std::move(book)); }

    bool checkOut(const std::string& title)
    {
        for (auto& book : m_books) {
            if (book.getTitle() == title) {
                return book.checkOut();
            }
        }
        return false;
    }

    void printStatus() const
    {
        for (const auto& book : m_books) {
            std::println("{:<14} {}", book.getTitle(),
                         book.isOnLoan() ? "대출 중" : "대출 가능");
        }
    }

private:
    std::vector<Book> m_books;
};

int main()
{
    Library library;
    library.add(Book{ "C++ Basics" });
    library.add(Book{ "Design Notes" });
    library.add(Book{ "Clean Style" });

    std::println("{}", library.checkOut("Design Notes"));
    std::println("{}", library.checkOut("Design Notes"));
    library.printStatus();

    // 대출 상태는 checkOut()을 거쳐야만 바뀐다. 직접 바꿀 길이 없다.
}
