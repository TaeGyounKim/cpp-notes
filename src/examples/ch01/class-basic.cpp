#include <print>
#include <string>

// ---- 클래스 정의: 무엇을 갖고 있고 무엇을 할 수 있는지 ----
class MovieTicket
{
public:
    MovieTicket();    // 생성자: 객체가 만들어질 때 자동으로 호출된다.
    ~MovieTicket();   // 소멸자: 객체가 사라질 때 자동으로 호출된다.

    int calculatePrice();

    std::string getTitle();
    void setTitle(std::string title);

    int getSeatCount();
    void setSeatCount(int seatCount);

    bool isMember();
    void setMember(bool member);

private:
    std::string m_title;
    int m_seatCount;
    bool m_member;
};

// ---- 멤버 함수의 정의: 클래스이름:: 을 앞에 붙인다 ----
MovieTicket::MovieTicket()
    : m_title{ "제목 없음" }
    , m_seatCount{ 1 }
    , m_member{ false }
{
    std::println("[표가 만들어짐]");
}

MovieTicket::~MovieTicket()
{
    std::println("[표가 사라짐]");
}

int MovieTicket::calculatePrice()
{
    int price{ getSeatCount() * 14000 };
    if (isMember()) {
        price -= 2000;   // 회원은 2000원 할인
    }
    return price;
}

std::string MovieTicket::getTitle() { return m_title; }
void MovieTicket::setTitle(std::string title) { m_title = title; }

int MovieTicket::getSeatCount() { return m_seatCount; }
void MovieTicket::setSeatCount(int seatCount) { m_seatCount = seatCount; }

bool MovieTicket::isMember() { return m_member; }
void MovieTicket::setMember(bool member) { m_member = member; }

// ---- 클래스 사용 ----
int main()
{
    MovieTicket ticket;
    std::println("{}: {}원", ticket.getTitle(), ticket.calculatePrice());

    ticket.setTitle("우주 여행");
    ticket.setSeatCount(2);
    ticket.setMember(true);
    std::println("{}: {}원", ticket.getTitle(), ticket.calculatePrice());

    // ticket.m_seatCount = 100;   // 오류: private 멤버는 밖에서 쓸 수 없다.
}
