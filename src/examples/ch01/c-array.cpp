#include <array>     // std::size
#include <cstddef>   // std::size_t
#include <print>

int main()
{
    int scores[3];       // int 세 칸. 아직 값은 정해지지 않았다.
    scores[0] = 90;      // 첫 칸의 번호는 0
    scores[1] = 75;
    scores[2] = 60;      // 마지막 칸의 번호는 크기 - 1
    std::println("{} {} {}", scores[0], scores[1], scores[2]);

    int zeros[3]{};              // 모두 0
    int partial[3]{ 7 };         // 7, 0, 0 (모자란 칸은 0)
    int numbers[]{ 1, 2, 3, 4 }; // 크기를 비우면 값의 개수로 정해진다.
    std::println("{} {} {}", zeros[0], zeros[1], zeros[2]);
    std::println("{} {} {}", partial[0], partial[1], partial[2]);

    // 칸의 개수 알아내기
    std::size_t count{ std::size(numbers) };
    std::size_t oldWay{ sizeof(numbers) / sizeof(numbers[0]) };
    std::println("{} {}", count, oldWay);

    // 2차원 배열: 3행 3열. 가운데 칸에 'o'를 놓는다.
    char board[3][3]{
        { '.', '.', '.' },
        { '.', '.', '.' },
        { '.', '.', '.' },
    };
    board[1][1] = 'o';
    std::println("{}{}{}", board[0][0], board[0][1], board[0][2]);
    std::println("{}{}{}", board[1][0], board[1][1], board[1][2]);
    std::println("{}{}{}", board[2][0], board[2][1], board[2][2]);
}
