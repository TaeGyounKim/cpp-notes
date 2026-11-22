#include <cstddef>
#include <print>
#include <vector>

// 방법 1: 행마다 따로 잡는 자유 저장소 2차원 배열
char** allocateBoard(std::size_t rows, std::size_t columns)
{
    char** board{ new char*[rows] };            // 첫째 차원: 포인터 배열
    for (std::size_t r{ 0 }; r < rows; ++r) {
        board[r] = new char[columns]{};         // 둘째 차원: 행마다
    }
    return board;
}

void releaseBoard(char**& board, std::size_t rows)
{
    for (std::size_t r{ 0 }; r < rows; ++r) {
        delete[] board[r];                      // 잡은 순서를 거꾸로
    }
    delete[] board;
    board = nullptr;
}

int main()
{
    // 스택의 2차원 배열: 메모리에는 한 줄로 이어져 놓인다.
    char grid[3][3]{};
    grid[0][0] = 'X';
    grid[2][1] = 'O';
    std::println("grid 크기: {}바이트", sizeof(grid));
    std::println("grid[1][0]은 grid[0][0]에서 {}칸 뒤",
                 &grid[1][0] - &grid[0][0]);

    std::size_t rows{ 2 };
    std::size_t columns{ 3 };
    char** board{ allocateBoard(rows, columns) };
    board[1][2] = 'X';
    std::println("board[1][2] = {}", board[1][2]);
    releaseBoard(board, rows);

    // 방법 2: 한 덩어리로 잡고 (행 * 열 개수 + 열)로 찾는다. 더 빠르다.
    std::vector<char> flat(rows * columns, '.');
    flat[1 * columns + 2] = 'X';
    std::println("flat[1][2] = {}", flat[1 * columns + 2]);

    // 방법 3: vector의 vector. 메모리 관리는 알아서 되지만 행마다 따로 잡힌다.
    std::vector<std::vector<char>> nested(rows, std::vector<char>(columns));
    nested[1][2] = 'X';
    std::println("nested[1][2] = {}", nested[1][2]);
}
