#include <print>

class Camera
{
public:
    Camera() { std::println("  Camera 생성"); }
    virtual ~Camera() { std::println("  Camera 소멸"); }
    virtual void takePhoto() { std::println("  찰칵"); }
    virtual void start() { std::println("  카메라 앱 시작"); }
};

class Player
{
public:
    Player() { std::println("  Player 생성"); }
    virtual ~Player() { std::println("  Player 소멸"); }
    virtual void play() { std::println("  음악 재생"); }
    virtual void start() { std::println("  플레이어 앱 시작"); }
};

// 두 클래스를 함께 상속한다. 생성은 나열한 순서, 소멸은 그 반대
class Phone : public Camera, public Player
{
public:
    // 두 부모에 같은 이름 start()가 있다. 어느 쪽인지 직접 정해 준다.
    void start() override { Player::start(); }
};

void snap(Camera& camera) { camera.takePhoto(); }   // Camera로 업캐스트
void listen(Player& player) { player.play(); }      // Player로 업캐스트

int main()
{
    std::println("만들기");
    {
        Phone phone;
        phone.takePhoto();       // Camera의 기능
        phone.play();            // Player의 기능
        snap(phone);
        listen(phone);
        phone.start();           // Phone이 정한 판(Player)
        phone.Camera::start();   // 특정 부모의 판을 직접 지정
    }
    std::println("끝");
}
