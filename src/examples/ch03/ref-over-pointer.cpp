#include <print>
#include <string>

struct Player
{
    std::string name;
    int score{ 0 };
};

// 포인터로 받기: nullptr일 수 있으므로 검사가 필요하다.
void addScoreByPointer(Player* player, int points)
{
    if (player == nullptr) {
        return;
    }
    player->score += points;
}

// 참조로 받기: 항상 실제 객체를 가리킨다. 검사가 필요 없다.
void addScore(Player& player, int points)
{
    player.score += points;
}

// 읽기만 한다면 const 참조. 선언만 봐도 바꾸지 않는다는 것을 안다.
void print(const Player& player)
{
    std::println("{}: {}", player.name, player.score);
}

int main()
{
    Player player{ "Kim" };

    addScoreByPointer(&player, 10);   // 부르는 쪽에서 &가 필요하다.
    addScore(player, 5);              // 보통 변수처럼 넘긴다.
    print(player);

    addScoreByPointer(nullptr, 10);   // 컴파일된다. 함수가 대비해야 한다.
    // addScore(nullptr, 10);         // 컴파일 오류
}
