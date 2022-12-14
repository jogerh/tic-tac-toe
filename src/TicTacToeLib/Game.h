#pragma once
#include "Board.h"

#include <optional>

/** Implementation of a single tic tac toe game

    This class provides an API for playing the game on a
    3 by 3 grid, and manages turns. To restart the game,
    create a new instance of this class.
*/
class Game {
public:
    /** */
    Game(Player firstPlayer);

    /** Returns true if the cell is empty and available */
    bool ValidMove(size_t col, size_t row);

    /** Marks the specified cell with the mark of the current player
        and switches turn */
    void MakeMove(size_t col, size_t row);

    /** Lets the computer choose a cell and switch turn. The
        maxDepth can be used to limit the recursion depth of
        the game logic. */
    void MakeCpuMove(size_t maxDepth);

    /** Evaluates the current game status */
    GameStatus GetGameStatus(Player player) const;

    /** Gets the player of the specified cell. If cell is
        free, empty is returned */
    std::optional<Player> GetPlayer(size_t col, size_t row) const;

    /** Get the player that will play the next move. */
    Player CurrentPlayer() const;

private:
    Player m_currentPlayer;
    Board m_board;
};
