#include <print>
#include <string>

class MovieTicket
{
public:
    // 데이터 멤버를 바꾸지 않는 멤버 함수에는 const를 붙인다.
    int calculatePrice() const { return m_seatCount * 14000; }
    std::string getTitle() const { return m_title; }
    int getSeatCount() const { return m_seatCount; }

    // 데이터 멤버를 바꾸는 멤버 함수에는 붙이지 않는다.
    void setTitle(std::string title) { m_title = title; }
    void setSeatCount(int seatCount) { m_seatCount = seatCount; }

private:
    std::string m_title{ "제목 없음" };
    int m_seatCount{ 1 };
};

int main()
{
    MovieTicket ticket;
    ticket.setSeatCount(2);
    std::println("{}", ticket.calculatePrice());

    // const 객체로는 const 멤버 함수만 부를 수 있다.
    const MovieTicket fixed;
    std::println("{} {}", fixed.getTitle(), fixed.calculatePrice());
    // fixed.setSeatCount(3);   // 오류
}
