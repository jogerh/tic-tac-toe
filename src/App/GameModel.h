#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QAbstractTableModel>
#include <Game.h>
#include <memory>

struct GameStatistics {
    Q_GADGET
    Q_PROPERTY(int Losses MEMBER m_losses)
    Q_PROPERTY(int Wins MEMBER m_wins)
    Q_PROPERTY(int Ties MEMBER m_ties)
public:
    int m_wins{};
    int m_losses{};
    int m_ties{};
};

/** A model that implements the TicTacToe game.

    The model maintains the board state, game state,
    and keeps track of the win/loss/tie statistics.

    The player always plays X, while the computer always
    plays O.
*/
class GameModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Status gameStatus READ getGameStatus NOTIFY gameStatusChanged)
    Q_PROPERTY(GameStatistics gameStats READ getGameStats NOTIFY gameStatusChanged)
    Q_PROPERTY(Difficulty difficulty WRITE setDifficulty)
public:
    enum class Status {
        HumanPlays,
        CpuPlays,
        Tie,
        HumanWin,
        HumanLoose
    };
    Q_ENUM(Status)

    enum class Difficulty {
        Easy,       ///< CPU player can score, but is unable to block
        Medium,     ///< CPU player can score and block, but has no clear strategy
        Impossible  ///< CPU player evaluates all possible outcomes before making a move
    };
    Q_ENUM(Difficulty)

    enum Roles {
        CellRole
    };

    QHash<int, QByteArray> roleNames() const override;
    explicit GameModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    /** Gets the board state for populating the board */
    QVariant data(const QModelIndex &index, int role) const override;

    /** Called when the human player makes a move */
    bool setData(const QModelIndex &index, const QVariant &, int role = Qt::EditRole) override;

    /** Restart the game */
    void revert() override;

    /** Checks whose turn it is, and if the game is over */
    Status getGameStatus();

    /** Returns a struct containing the current game statistics */
    GameStatistics getGameStats();

    /** Changes the CPU player's ability to predict future moves */
    void setDifficulty(Difficulty difficulty);
signals:
    /** Notified whenever the game status may ahve changed,
        for example if a player has made a move */
    void gameStatusChanged();

public slots:
    /** Let the CPU player make a move */
    void playCpu();

private:
    size_t m_maxDepth = std::numeric_limits<size_t>::max();
    std::unique_ptr<Game> m_game;
    GameStatistics m_stats;
};
