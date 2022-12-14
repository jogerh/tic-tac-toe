#include "Game.h"
#include "GameLogic.h"
#include <cassert>

Game::Game(Player firstPlayer)
    : m_currentPlayer{firstPlayer}
{
}

bool Game::ValidMove(size_t col, size_t row)
{
    return !m_board.GetCell(col + m_board.Columns() * row).has_value();
}

void Game::MakeMove(size_t col, size_t row)
{
    assert(ValidMove(col, row));

    m_board.SetCell(col + m_board.Columns() * row, m_currentPlayer);
    m_currentPlayer = Toggle(m_currentPlayer);
}

void Game::MakeCpuMove(size_t maxDepth)
{
    if (const auto move = GetBestMove(m_board, m_currentPlayer, maxDepth); move.has_value()) {
        m_board.SetCell(move.value(), m_currentPlayer);
        m_currentPlayer = Toggle(m_currentPlayer);
    }
}

GameStatus Game::GetGameStatus(Player player) const
{
    return m_board.GetGameStatus(player);
}

std::optional<Player> Game::GetPlayer(size_t col, size_t row) const
{
    return m_board.GetCell(col + m_board.Columns() * row);
}

Player Game::CurrentPlayer() const
{
    return m_currentPlayer;
}
