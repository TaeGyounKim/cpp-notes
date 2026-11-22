#include <memory>
#include <print>

// shared_ptr끼리 서로 가리키면 참조 횟수가 0이 되지 않는다.
struct Team;

struct Member
{
    std::shared_ptr<Team> team;   // 멤버가 팀을 소유?
    ~Member() { std::println("  Member 소멸"); }
};

struct Team
{
    std::shared_ptr<Member> leader;
    ~Team() { std::println("  Team 소멸"); }
};

// 고친 판: 거꾸로 가리키는 쪽을 weak_ptr로
struct FixedTeam;

struct FixedMember
{
    std::weak_ptr<FixedTeam> team;   // 소유하지 않고 가리키기만
    ~FixedMember() { std::println("  FixedMember 소멸"); }
};

struct FixedTeam
{
    std::shared_ptr<FixedMember> leader;
    ~FixedTeam() { std::println("  FixedTeam 소멸"); }
};

int main()
{
    std::println("순환: shared_ptr <-> shared_ptr");
    {
        auto team{ std::make_shared<Team>() };
        auto member{ std::make_shared<Member>() };
        team->leader = member;
        member->team = team;
    }
    std::println("  (아무것도 소멸하지 않았다: 누수)");

    std::println("한쪽을 weak_ptr로");
    {
        auto team{ std::make_shared<FixedTeam>() };
        auto member{ std::make_shared<FixedMember>() };
        team->leader = member;
        member->team = team;
    }
    std::println("끝");
}
