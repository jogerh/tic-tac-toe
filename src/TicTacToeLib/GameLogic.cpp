#include "GameLogic.h"
#include "Board.h"
#include <limits>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>
namespace {

struct Move {
    int Score{};
    std::optional<size_t> Position{};
};

/** Returns numbers 0-8 in random order */
std::array<size_t, 9> RandomMoves() {
    std::array<size_t, 9> values;
    iota(begin(values), end(values), 0u);

    std::random_device rd;
    std::mt19937 g(rd());

    shuffle(begin(values), end(values), g);

    return values;
}

Move EvaluateNextMove(Board &board, Player player, size_t depth) {

    // If game is alredy completed, return the
    // score of the current outcome
    switch (board.GetGameStatus(player)) {
    case GameStatus::Loose:
        return {.Score = -1};
    case GameStatus::Win:
        return {.Score = 1};
    case GameStatus::Tie:
        return {.Score = 0};
    case GameStatus::InProgress:
        break;
    }

    if (depth == 0u)
        return {.Score = 0}; // Depth reached: undecisive

    // We are still playing. Pretend to play all possible
    // combination of empty squares and find the move that has
    // the highest chance of winning
    Move bestMove{.Score = std::numeric_limits<int>::min()};

    // Give some randomness if all moves are equally good
    // to make game more fun in easy levels
    for(const auto pos : RandomMoves()) {
        if (board.GetCell(pos).has_value())
            continue;

        board.SetCell(pos, player);

        // Recurse through all possible outcomes
        Move move{
            .Score = -EvaluateNextMove(board, Toggle(player), depth - 1u).Score,
            .Position = pos,
        };

        board.ClearCell(pos);

        if (move.Score > bestMove.Score)
            bestMove = move;
    }
    return bestMove;
}
}

std::optional<size_t> GetBestMove(Board board, Player player, size_t maxDepth) {
    return EvaluateNextMove(board, player, maxDepth).Position;
}
