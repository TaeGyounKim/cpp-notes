#include <print>
#include <string>

class MovieTicket
{
public:
    // 멤버 함수를 클래스 정의 안에 바로 적을 수도 있다.
    int calculatePrice()
    {
        int price{ m_seatCount * 14000 };
        if (m_member) {
            price -= 2000;
        }
        return price;
    }

    std::string getTitle() { return m_title; }
    void setTitle(std::string title) { m_title = title; }

    void setSeatCount(int seatCount) { m_seatCount = seatCount; }
    void setMember(bool member) { m_member = member; }

private:
    // 클래스 내부 초기화: 생성자를 쓰지 않고 첫 값을 정한다.
    std::string m_title{ "제목 없음" };
    int m_seatCount{ 1 };
    bool m_member{ false };
};

int main()
{
    MovieTicket ticket;
    std::println("{}: {}원", ticket.getTitle(), ticket.calculatePrice());

    ticket.setTitle("바다 탐험");
    ticket.setSeatCount(3);
    std::println("{}: {}원", ticket.getTitle(), ticket.calculatePrice());
}
