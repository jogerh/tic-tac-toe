#include "Board.h"
#include <cassert>
#include <algorithm>

namespace {

// Lookup table containing triplets of indices representing
// rows, columns and diagonals.
constexpr std::array<std::array<size_t, 3>, 8> WinningCombos {
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertical
        {0, 4, 8}, {6, 4, 2}             // Diagonal
    }
};

}

size_t Board::Size()
{
    return m_columns * m_columns;
}

size_t Board::Columns()
{
    return m_columns;
}

void Board::SetCell(size_t pos, Player player)
{
    assert(!m_grid[pos].has_value());
    m_grid[pos] = player;
}

void Board::ClearCell(size_t pos) {
    m_grid[pos] = {};
}

std::optional<Player> Board::GetCell(size_t pos) const
{
    assert (pos < m_grid.size());
    return m_grid[pos];
}

GameStatus Board::GetGameStatus(Player player) const
{
    // Check if there is a winner yet (3 in a row)
    for (const auto& [i0, i1, i2] : WinningCombos) {

        if (m_grid[i0].has_value() && m_grid[i0] == m_grid[i1] && m_grid[i0] == m_grid[i2]) {
            if (*m_grid[i0] == player)
                return GameStatus::Win;
            else
                return GameStatus::Loose;
        }

    }

    if (!HasEmptyCells())
        return GameStatus::Tie;

    else
        return GameStatus::InProgress;
}

bool Board::HasEmptyCells() const
{
    return any_of(begin(m_grid), end(m_grid), [](const std::optional<Player>& tileValue) {
        return !tileValue.has_value();
    });
}
