#include <print>
#include <utility>

// 두 열거형에 같은 이름 Unknown이 있지만 충돌하지 않는다.
enum class Door { Open, Closed, Unknown };
enum class Network { Connected, Disconnected, Unknown };

int main()
{
    Door door{ Door::Unknown };
    Network network{ Network::Unknown };
    std::println("{} {}", std::to_underlying(door),
                 std::to_underlying(network));

    {
        // 이 블록 안에서는 Door:: 를 생략할 수 있다.
        using enum Door;
        door = Closed;
    }

    {
        // Connected 하나만 생략할 수 있다.
        using Network::Connected;
        network = Connected;
        network = Network::Disconnected;   // 나머지는 Network:: 필요
    }

    std::println("{} {}", std::to_underlying(door),
                 std::to_underlying(network));
}
