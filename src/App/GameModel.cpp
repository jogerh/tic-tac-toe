#include "GameModel.h"
#include <qpoint.h>

QHash<int, QByteArray> GameModel::roleNames() const {
    return {
        { CellRole, "value" }
    };
}

GameModel::GameModel(QObject* parent)
    : QAbstractTableModel{parent}
    ,  m_game{std::make_unique<Game>(Player::X)}
{
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (role != CellRole)
        return QVariant();

    const int col = index.column();
    const int row = index.row();
    if (col < 0 || row < 0)
        return QVariant();

    const auto player = m_game->GetPlayer(col, row);
    if (player == Player::X)
        return "X";

    if (player == Player::O)
        return "O";

    return "";
}

bool GameModel::setData(const QModelIndex &cellIndex, const QVariant&, int role)
{
    if (role != CellRole)
        return false;

    const int col = cellIndex.column();
    const int row = cellIndex.row();
    if (col < 0 || row < 0)
        return false;

    if (!m_game->ValidMove(col, row))
        return false;

    if (m_game->GetGameStatus(Player::X) != GameStatus::InProgress)
        return false;

    if (m_game->CurrentPlayer() != Player::X)
        return false;

    m_game->MakeMove(col, row);

    emit dataChanged(index(0, 0), index(2, 2), {role});
    emit gameStatusChanged();
    return true;
}

void GameModel::playCpu()
{
    if (m_game->CurrentPlayer() != Player::O)
        return;

    if (m_game->GetGameStatus(Player::X) != GameStatus::InProgress)
        return;

    m_game->MakeCpuMove(m_maxDepth);

    emit dataChanged(index(0, 0), index(2, 2), {CellRole});
    emit gameStatusChanged();
}

GameModel::Status GameModel::getGameStatus() {
    switch (m_game->GetGameStatus(Player::X)) {

    case GameStatus::Tie:
        return Status::Tie;
    case GameStatus::Win:
        return Status::HumanWin;
    case GameStatus::Loose:
        return Status::HumanLoose;
    default:
        return m_game->CurrentPlayer() == Player::O ? Status::CpuPlays : Status::HumanPlays;
    }

}

GameStatistics GameModel::getGameStats()
{
    return m_stats;
}

void GameModel::setDifficulty(Difficulty difficulty)
{
    size_t maxDepth = std::numeric_limits<size_t>::max();
    if (difficulty == Difficulty::Easy)
        maxDepth = 1u;
    else if (difficulty == Difficulty::Medium)
        maxDepth = 2u;

    m_maxDepth = maxDepth;
}

void GameModel::revert()
{
    GameStatus status = m_game->GetGameStatus(Player::X);
    if (status == GameStatus::Win)
        ++m_stats.m_wins;
    else if (status == GameStatus::Loose)
        ++m_stats.m_losses;
    else if (status == GameStatus::Tie)
        ++m_stats.m_ties;

    // Human gets to start only if previous game was lost.
    const auto starts = status == GameStatus::Loose ? Player::X : Player::O;
    m_game = std::make_unique<Game>(starts);
    emit dataChanged(index(0, 0), index(2, 2), {CellRole});
    emit gameStatusChanged();
}



