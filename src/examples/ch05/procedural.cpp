#include <print>
#include <string>
#include <vector>

// 절차적 방식: "이 프로그램은 무엇을 하는가"에서 출발한다.
// 데이터(구조체)와 그것을 다루는 함수가 따로 있다.

struct Book
{
    std::string title;
    bool isOnLoan{ false };
};

std::vector<Book> loadBooks()
{
    return { { "C++ Basics" }, { "Design Notes" }, { "Clean Style" } };
}

Book* findBook(std::vector<Book>& books, const std::string& title)
{
    for (auto& book : books) {
        if (book.title == title) {
            return &book;
        }
    }
    return nullptr;
}

bool checkOut(std::vector<Book>& books, const std::string& title)
{
    Book* book{ findBook(books, title) };
    if (book == nullptr || book->isOnLoan) {
        return false;
    }
    book->isOnLoan = true;
    return true;
}

void printStatus(const std::vector<Book>& books)
{
    for (const auto& book : books) {
        std::println("{:<14} {}", book.title,
                     book.isOnLoan ? "대출 중" : "대출 가능");
    }
}

int main()
{
    // 하는 일의 순서가 그대로 프로그램의 구조다.
    std::vector<Book> books{ loadBooks() };
    std::println("{}", checkOut(books, "Design Notes"));
    std::println("{}", checkOut(books, "Design Notes"));
    printStatus(books);

    // 데이터가 열려 있어서, 규칙을 건너뛰는 코드도 막을 수 없다.
    books[0].isOnLoan = true;
}
