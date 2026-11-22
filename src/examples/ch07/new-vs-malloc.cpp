#include <cstdlib>
#include <new>
#include <print>
#include <string>

class Ticket
{
public:
    Ticket() : m_seat{ "A-1" } { std::println("  생성자: 좌석 {}", m_seat); }
    ~Ticket() { std::println("  소멸자"); }
    const std::string& getSeat() const { return m_seat; }

private:
    std::string m_seat;
};

int main()
{
    std::println("new / delete");
    Ticket* ticket{ new Ticket{} };   // 메모리를 잡고 생성자를 부른다.
    std::println("  좌석: {}", ticket->getSeat());
    delete ticket;                    // 소멸자를 부르고 메모리를 돌려준다.
    ticket = nullptr;

    std::println("malloc / free");
    // 메모리만 잡는다. 생성자가 불리지 않아 m_seat는 만들어지지 않았다.
    void* raw{ std::malloc(sizeof(Ticket)) };
    std::println("  {}바이트를 잡았지만 생성자 출력이 없다", sizeof(Ticket));
    // static_cast<Ticket*>(raw)->getSeat()를 부르면 정의되지 않은 동작
    std::free(raw);                   // 소멸자도 불리지 않는다.
}
