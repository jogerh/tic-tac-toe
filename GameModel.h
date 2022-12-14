#ifndef BOARD_H
#define BOARD_H

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
        Easy,
        Medium,
        Impossible
    };
    Q_ENUM(Difficulty)

    enum Roles {
        CellRole
    };

    QHash<int, QByteArray> roleNames() const override;
    explicit GameModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &, int role = Qt::EditRole) override;

    void revert() override;

    Status getGameStatus();
    GameStatistics getGameStats();

    void setDifficulty(Difficulty difficulty);
signals:
    void gameStatusChanged();

public slots:
    void playCpu();

private:
    size_t m_maxDepth = std::numeric_limits<size_t>::max();
    std::unique_ptr<Game> m_game;
    GameStatistics m_stats;
};



#endif // BOARD_H
