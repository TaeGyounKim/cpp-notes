#include <print>

// 함수 안의 static 지역 변수: 처음 지날 때 한 번 초기화되고,
// 함수가 끝나도 값이 남는다.
int nextTicket()
{
    static int counter{ 100 };
    return ++counter;
}

class Station
{
public:
    static int s_created;    // 클래스에 하나뿐인 데이터 멤버
};
int Station::s_created{ 7 }; // 같은 파일 안에서는 나온 순서대로 초기화
int g_after{ Station::s_created * 2 };   // 그래서 s_created가 먼저

int main()
{
    std::println("{}", nextTicket());
    std::println("{}", nextTicket());
    std::println("{}", nextTicket());
    std::println("s_created {}, g_after {}", Station::s_created, g_after);
}
