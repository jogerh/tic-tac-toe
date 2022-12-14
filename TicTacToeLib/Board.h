#pragma once
#include <optional>
#include <array>

/** Representation of a player as a cross or a circle */
enum class Player { O, X };

enum class GameStatus {
    InProgress,
    Tie,
    Win,
    Loose
};

/** Tic Tac Toe playing area.

    This class represents a 3 by 3 grid on a piece of paper. Each square
    is represented by a cell which may be empty or have a cross or a circle.

    The board can be used to assess the current status of the game, if the
    game is over, if there is a winner, or if there is a tie.
*/
class Board {
public:
    /** Get the number of cells on the board (9) */
    static size_t Size();

    /** Get the number of columns on the board (3) */
    static size_t Columns();

    /** Sets a cross or a circle in a cell */
    void SetCell(size_t pos, Player player);

    /** Gets the value of a cell. It can be empty, or taken
        by one of the players */
    std::optional<Player> GetCell(size_t pos) const;

    /** Set a cell back to its empty state */
    void ClearCell(size_t pos);

    /** Determine if the player is a winner, looser, or if the game
        is a tie still in progress */
    GameStatus GetGameStatus(Player player) const;

private:
    bool HasEmptyCells() const;

    static inline constexpr size_t m_columns = 3;
    std::array<std::optional<Player>, m_columns * m_columns> m_grid;
};
