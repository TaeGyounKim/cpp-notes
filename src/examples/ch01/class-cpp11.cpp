#include <iostream>
#include <string>

// 클래스 내부 초기화와 중괄호 초기화는 C++11에서도 쓸 수 있다.
class MovieTicket
{
public:
    int calculatePrice() { return m_seatCount * 14000; }
    void setSeatCount(int seatCount) { m_seatCount = seatCount; }

private:
    std::string m_title{ "untitled" };
    int m_seatCount{ 1 };
};

struct Product
{
    char grade;
    int id;
    int stock;
    int price;
};

int main()
{
    MovieTicket ticket;
    ticket.setSeatCount(2);
    std::cout << ticket.calculatePrice() << '\n';

    // 지정 초기화 대신: 선언 순서대로 값을 나열한다.
    Product a{ 'A', 1024, 50, 4500 };
    std::cout << a.grade << ' ' << a.id << ' ' << a.stock << ' '
              << a.price << '\n';
}
