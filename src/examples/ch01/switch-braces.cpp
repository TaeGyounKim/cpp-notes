#include <print>

int main()
{
    int level{ 2 };
    int score{ 0 };

    // 초기화 구문: bonus는 이 switch 문 안에서만 쓴다.
    switch (int bonus{ 10 }; level) {
        case 1:
            score = bonus;
            break;
        case 2: {
            // case 안에서 변수를 만들려면 중괄호로 감싼다.
            int doubled{ bonus * 2 };
            score = doubled;
            break;
        }
        default:
            break;
    }

    std::println("{}", score);
}
