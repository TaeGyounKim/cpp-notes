#include <print>
#include <string>
#include <string_view>
#include <vector>

// I: 인터페이스 분리. 큰 인터페이스 하나 대신 작은 인터페이스 둘
class Printer
{
public:
    virtual ~Printer() = default;
    virtual void print(std::string_view document) = 0;
};

class Scanner
{
public:
    virtual ~Scanner() = default;
    virtual std::string scan() = 0;
};

// 인쇄만 하는 기기는 Printer만 구현한다. 쓸 일 없는 scan()을 떠안지 않는다.
class SimplePrinter : public Printer
{
public:
    void print(std::string_view document) override
    {
        std::println("[인쇄] {}", document);
    }
};

// 복합기는 둘 다 구현한다.
class MultiFunctionDevice : public Printer, public Scanner
{
public:
    void print(std::string_view document) override
    {
        std::println("[복합기 인쇄] {}", document);
    }
    std::string scan() override { return "스캔한 계약서"; }
};

// D: 의존 관계 역전. 높은 수준의 Office는 구체적인 기기가 아니라
// Printer라는 인터페이스에 기댄다. 어떤 프린터인지는 밖에서 넣어 준다.
class Office
{
public:
    explicit Office(Printer& printer) : m_printer{ printer } {}

    void printReport(const std::vector<std::string>& lines)
    {
        for (const auto& line : lines) {
            m_printer.print(line);
        }
    }

private:
    Printer& m_printer;
};

int main()
{
    SimplePrinter cheap;
    MultiFunctionDevice deluxe;

    Office small{ cheap };
    small.printReport({ "1분기 매출" });

    Office large{ deluxe };
    large.printReport({ "1분기 매출", "2분기 매출" });

    std::println("{}", deluxe.scan());
}
