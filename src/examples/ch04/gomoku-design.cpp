#include <cstddef>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>

enum class Stone { None, Black, White };

// ---- 모델: 판의 상태와 규칙 ----
class Board
{
public:
    static constexpr int Size{ 9 };

    bool isInside(int row, int column) const
    {
        return row >= 0 && row < Size && column >= 0 && column < Size;
    }

    Stone getStoneAt(int row, int column) const
    {
        return m_cells[toIndex(row, column)];
    }

    void placeStone(int row, int column, Stone stone)
    {
        if (getStoneAt(row, column) != Stone::None) {
            throw std::logic_error{ "cell is not empty" };
        }
        m_cells[toIndex(row, column)] = stone;
    }

    // 방금 놓은 자리에서 네 방향으로 같은 돌이 5개 이상 이어졌는지 본다.
    bool isWinningMove(int row, int column) const
    {
        const Stone stone{ getStoneAt(row, column) };
        const int directions[4][2]{ { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, -1 } };
        for (const auto& direction : directions) {
            const int count{ 1
                + countFrom(row, column, direction[0], direction[1], stone)
                + countFrom(row, column, -direction[0], -direction[1],
                            stone) };
            if (count >= 5) {
                return true;
            }
        }
        return false;
    }

private:
    std::size_t toIndex(int row, int column) const
    {
        if (!isInside(row, column)) {
            throw std::out_of_range{ "outside the board" };
        }
        return static_cast<std::size_t>(row * Size + column);
    }

    int countFrom(int row, int column, int dRow, int dColumn,
                  Stone stone) const
    {
        int count{ 0 };
        row += dRow;
        column += dColumn;
        while (isInside(row, column) && getStoneAt(row, column) == stone) {
            ++count;
            row += dRow;
            column += dColumn;
        }
        return count;
    }

    std::vector<Stone> m_cells{ std::vector<Stone>(Size * Size, Stone::None) };
};

// ---- 뷰: 판을 보여 주는 방법 ----
class BoardView
{
public:
    virtual ~BoardView() = default;
    virtual void draw(const Board& board) = 0;
};

class ConsoleBoardView : public BoardView
{
public:
    void draw(const Board& board) override
    {
        for (int row{ 0 }; row < Board::Size; ++row) {
            for (int column{ 0 }; column < Board::Size; ++column) {
                const Stone stone{ board.getStoneAt(row, column) };
                std::print("{} ", stone == Stone::Black   ? 'X'
                                  : stone == Stone::White ? 'O'
                                                          : '.');
            }
            std::println("");
        }
    }
};

// ---- 컨트롤러: 둘 자리를 정해서 모델을 바꾼다 ----
class Player
{
public:
    virtual ~Player() = default;
    // 돌을 하나 놓고, 놓은 자리를 돌려준다.
    virtual std::pair<int, int> takeTurn(Board& board, Stone stone) = 0;
};

// 미리 정해 둔 수를 차례로 두는 플레이어. 키보드 없이 시험할 수 있다.
class ScriptedPlayer : public Player
{
public:
    explicit ScriptedPlayer(std::vector<std::pair<int, int>> moves)
        : m_moves{ std::move(moves) }
    {
    }

    std::pair<int, int> takeTurn(Board& board, Stone stone) override
    {
        while (true) {
            const auto [row, column]{ m_moves.at(m_next++) };
            // 사용자 오류: 프로그램을 끝내지 않고 다음 입력을 받는다.
            if (!board.isInside(row, column)
                || board.getStoneAt(row, column) != Stone::None) {
                std::println("({}, {})에는 둘 수 없음. 다시 입력", row, column);
                continue;
            }
            board.placeStone(row, column, stone);
            return { row, column };
        }
    }

private:
    std::vector<std::pair<int, int>> m_moves;
    std::size_t m_next{ 0 };
};

// ---- 게임 진행: 차례를 돌리고 승패를 알린다 ----
class Game
{
public:
    Game(Player& black, Player& white, BoardView& view)
        : m_black{ black }, m_white{ white }, m_view{ view }
    {
    }

    void play()
    {
        for (int turn{ 0 }; turn < Board::Size * Board::Size; ++turn) {
            const bool isBlackTurn{ turn % 2 == 0 };
            Player& player{ isBlackTurn ? m_black : m_white };
            const Stone stone{ isBlackTurn ? Stone::Black : Stone::White };

            const auto [row, column]{ player.takeTurn(m_board, stone) };
            if (m_board.isWinningMove(row, column)) {
                m_view.draw(m_board);
                std::println("{} 승리", isBlackTurn ? "흑(X)" : "백(O)");
                return;
            }
        }
        m_view.draw(m_board);
        std::println("무승부");
    }

private:
    Board m_board;
    Player& m_black;
    Player& m_white;
    BoardView& m_view;
};

int main()
{
    ScriptedPlayer black{
        { { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 4, 6 } }
    };
    // 백의 셋째 수 (4, 4)는 이미 돌이 있는 자리다.
    ScriptedPlayer white{
        { { 5, 2 }, { 5, 3 }, { 4, 4 }, { 5, 4 }, { 5, 5 } }
    };
    ConsoleBoardView view;

    Game game{ black, white, view };
    game.play();
}
