#pragma once
#include "Board.h"
#include <optional>
#include <limits>

/** Find the best move to play.

    GetBestMove goes recursively through all potential moves up
    to maxDepth moves and select the move that has the best
    chance of winning. An easier game is achieved by reducing
    the depth of the search algorithm.

    depth = 1: Attempts to get 3 in a row, but is unable to block
    depth = 2: Attempts to get 3 in a row, and is able to block next move
    depth = 3-infinity: Able to evaluate more future moves

    If board is not full, the function returns the index to the
    board cell that has the highest likelihood of winning,
    otherwise empty.
*/
std::optional<size_t> GetBestMove(Board board, Player player, size_t maxDepth = std::numeric_limits<size_t>::max());
