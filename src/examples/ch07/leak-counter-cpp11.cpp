#include <iostream>

class Tracked
{
public:
    Tracked() { ++s_alive; }
    ~Tracked() { --s_alive; }
    static int alive() { return s_alive; }

private:
    // inline 변수(C++17)가 없으면 static 데이터 멤버는 클래스 밖에 정의한다.
    static int s_alive;
};

int Tracked::s_alive{ 0 };

void leaky()
{
    new Tracked{};
}

int main()
{
    for (int i{ 0 }; i < 3; ++i) {
        leaky();
    }
    std::cout << "남은 객체: " << Tracked::alive() << '\n';
}
