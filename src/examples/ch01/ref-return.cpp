#include <print>
#include <string>

class MovieTicket
{
public:
    // 복사하지 않고 데이터 멤버를 읽기 전용으로 내준다.
    const std::string& getTitle() const { return m_title; }
    void setTitle(const std::string& title) { m_title = title; }

private:
    std::string m_title{ "제목 없음" };
};

int main()
{
    MovieTicket ticket;
    ticket.setTitle("우주 여행");

    const std::string& title{ ticket.getTitle() };
    std::println("{}", title);
}
