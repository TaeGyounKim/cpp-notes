#include <print>
#include <string>
#include <vector>

class Button
{
public:
    explicit Button(std::string label) : m_label{ label } {}
    ~Button() { std::println("  버튼 '{}' 사라짐", m_label); }

private:
    std::string m_label;
};

// 합성: 창이 버튼을 데이터 멤버로 직접 가진다.
// 창이 사라지면 버튼도 함께 사라진다.
class Window
{
public:
    Window() : m_ok{ "확인" }, m_cancel{ "취소" } {}
    ~Window() { std::println("  창 사라짐"); }

private:
    Button m_ok;
    Button m_cancel;
};

class Player
{
public:
    explicit Player(std::string name) : m_name{ name } {}
    ~Player() { std::println("  선수 '{}' 사라짐", m_name); }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
};

// 집합: 팀은 선수를 가리키기만 한다. 선수는 팀 밖에서 따로 산다.
// 팀이 해체돼도 선수는 남는다.
class Team
{
public:
    void add(Player& player) { m_members.push_back(&player); }
    ~Team()
    {
        std::println("  팀 해체 (선수 {}명은 그대로)", m_members.size());
    }

private:
    std::vector<Player*> m_members;
};

int main()
{
    std::println("[합성]");
    {
        Window window;
    }   // 여기서 창과 버튼이 함께 사라진다.

    std::println("[집합]");
    Player kim{ "Kim" };
    Player lee{ "Lee" };
    {
        Team team;
        team.add(kim);
        team.add(lee);
    }   // 여기서는 팀만 사라진다.
    std::println("  남은 선수: {}, {}", kim.getName(), lee.getName());
}
