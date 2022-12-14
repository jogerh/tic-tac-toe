#include <Board.h>
#include <GameLogic.h>
#include <Game.h>
#include <gtest/gtest.h>

TEST(BoardTests, RequireThat_Constructor_CreatesEmptyBoard) {
    Board board;

    for(size_t i = 0; i < board.Size(); ++i)
        EXPECT_FALSE(board.GetCell(i).has_value());
}

TEST(BoardTests, RequireThat_SetCell_SetsCellValue) {
    Board board;
    board.SetCell(3, Player::X);

    EXPECT_EQ(board.GetCell(3), Player::X);
    ASSERT_FALSE(board.GetCell(2).has_value());
}

TEST(BoardTests, RequireThat_ClearCell_ClearsCell) {
    Board board;
    board.SetCell(3, Player::O);
    board.ClearCell(3);

    EXPECT_FALSE(board.GetCell(3).has_value());
}

TEST(BoardTests, RequireThat_GetGameStatus_ReturnsInProgress_WhenBoardIsEmpty) {
    Board board;
    EXPECT_EQ(board.GetGameStatus(Player::X), GameStatus::InProgress);
}

// Board layout:
//
// 0 1 2
// 3 4 5
// 6 7 8

TEST(BoardTests, RequireThat_GetGameStatus_ReturnsWin_WhenPlayerWonWithRow) {
    Board board;
    for(const auto& pos : {3u, 4u, 5u})
        board.SetCell(pos, Player::O);

    EXPECT_EQ(board.GetGameStatus(Player::O), GameStatus::Win);
    EXPECT_EQ(board.GetGameStatus(Player::X), GameStatus::Loose);
}

TEST(BoardTests, RequireThat_GetGameStatus_ReturnsWin_WhenPlayerWonWithColumn) {
    Board board;
    for(const auto& pos : {2u, 5u, 8u})
        board.SetCell(pos, Player::O);

    EXPECT_EQ(board.GetGameStatus(Player::O), GameStatus::Win);
    EXPECT_EQ(board.GetGameStatus(Player::X), GameStatus::Loose);
}

TEST(BoardTests, RequireThat_GetGameStatus_ReturnsWin_WhenPlayerWonWithDiagnoal) {
    Board board;
    for(const auto& pos : {2u, 4u, 6u})
        board.SetCell(pos, Player::O);

    EXPECT_EQ(board.GetGameStatus(Player::O), GameStatus::Win);
    EXPECT_EQ(board.GetGameStatus(Player::X), GameStatus::Loose);
}

TEST(BoardTests, RequireThat_GetGameStatus_ReturnsTie_WhenBoardIsFullWithoutWinner) {
    Board board;
    for(const auto& pos : {0u, 2u, 3u, 5u, 7u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {1u, 4u, 6u, 8u})
        board.SetCell(pos, Player::X);

    EXPECT_EQ(board.GetGameStatus(Player::O), GameStatus::Tie);
    EXPECT_EQ(board.GetGameStatus(Player::X), GameStatus::Tie);
}

TEST(GameLogicTests, RequireThat_GetBestMove_ReturnsEmpty_WhenBoardIsFull) {
    // O X O
    // O X O
    // X O X
    Board board;
    for(const auto& pos : {0u, 2u, 3u, 5u, 7u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {1u, 4u, 6u, 8u})
        board.SetCell(pos, Player::X);

    EXPECT_FALSE(GetBestMove(board, Player::X).has_value());
}


TEST(GameLogicTests, RequireThat_GetBestMove_ReturnsLastEmptyCell_WhenOnlyOneCellRemaining) {
    // O X O
    // O X O
    // X O _
    Board board;
    for(const auto& pos : {0u, 2u, 3u, 5u, 7u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {1u, 4u, 6u})
        board.SetCell(pos, Player::X);

    EXPECT_EQ(GetBestMove(board, Player::X), 8u);
}

TEST(GameLogicTests, RequireThat_GetBestMove_ReturnsWinningMove_WhenTwoCellsRemaining) {
    // X O O
    // O X O
    // X _ _
    Board board;
    for(const auto& pos : {1u, 2u, 3u, 5u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {0u, 4u, 6u})
        board.SetCell(pos, Player::X);

    EXPECT_EQ(*GetBestMove(board, Player::X), 8u);
    EXPECT_EQ(*GetBestMove(board, Player::O), 8u);
}

TEST(GameLogicTests, RequireThat_GetBestMove_Blocks_WhenOponentCanWin_AndDepthIs2) {
    // O O _
    // X _ _
    // X _ _
    Board board;
    for(const auto& pos : {0u, 1u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {3u, 6u})
        board.SetCell(pos, Player::X);

    // Need to reduce search depth because X will eventually loose
    // No move is better than the other for the end game. With a
    // lower depth, the eventual loss is not visible, and blocking
    // is the best option.
    EXPECT_EQ(*GetBestMove(board, Player::X, 2u), 2u);
}

TEST(GameLogicTests, RequireThat_GetBestMove_TakesWin_WhenDepthIs1) {
    // O O _
    // X _ _
    // X _ _
    Board board;
    for(const auto& pos : {0u, 1u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {3u, 6u})
        board.SetCell(pos, Player::X);

    // In easy mode, we want the algorithm to take any wins
    // that may show up, even if it is unable to have any
    // strategy
    EXPECT_EQ(*GetBestMove(board, Player::O, 1u), 2u);
}

TEST(GameLogicTests, RequireThat_GetBestMove_ChoosesWinningMove_WhenNextMoveCanWin) {
    // O O _
    // X X _
    // _ _ _
    Board board;
    for(const auto& pos : {0u, 1u})
        board.SetCell(pos, Player::O);

    for(const auto& pos : {3u, 4u})
        board.SetCell(pos, Player::X);

    auto bestMoveX = *GetBestMove(board, Player::X);
    EXPECT_TRUE(bestMoveX == 2u || bestMoveX == 5u); // Not intuitive to block, but X will anyway win in next move
    EXPECT_EQ(*GetBestMove(board, Player::O), 2u);
}

TEST(GameTests, RequireThat_ValidMove_ReturnsTrueOnAnyCell_WhenGameStarted) {
    Game game{Player::X};
    for(size_t row = 0; row < Board::Columns(); ++row) {
        for(size_t col = 0; col < Board::Columns(); ++col) {
            EXPECT_TRUE(game.ValidMove(col, row));
        }
    }
}

TEST(GameTests, RequireThat_ValidMove_ReturnsFalse_WhenCellIsNotEmpty) {
    Game game{Player::X};
    game.MakeMove(1u, 2u);
    EXPECT_FALSE(game.ValidMove(1u, 2u));
}

TEST(GameTests, RequireThat_MakeMove_TogglesPlayer) {
    Game game{Player::O};

    ASSERT_EQ(game.CurrentPlayer(), Player::O);
    game.MakeMove(2u, 2u);
    EXPECT_EQ(game.CurrentPlayer(), Player::X);
}

TEST(GameTests, RequireThat_MakeCpuMove_TogglesPlayer) {
    Game game{Player::O};

    ASSERT_EQ(game.CurrentPlayer(), Player::O);
    game.MakeCpuMove(3u);
    EXPECT_EQ(game.CurrentPlayer(), Player::X);
}

TEST(GameTests, RequireThat_GetPlayer_ReturnsEmpty_WhenCellIsEmpty) {
    Game game{Player::O};

    EXPECT_FALSE(game.GetPlayer(1u, 2u).has_value());
}

TEST(GameTests, RequireThat_GetPlayer_ReturnsX_WhenWhenCellTakenByX) {
    Game game{Player::X};

    game.MakeMove(2u, 1u);
    EXPECT_EQ(game.GetPlayer(2u, 1u), Player::X);
}

TEST(GameTests, RequireThat_MakeCpuMove_PopulatesACell) {
    Game game{Player::X};
    game.MakeCpuMove(3u);

    size_t availableMoves = 0u;
    for(size_t row = 0; row < Board::Columns(); ++row) {
        for(size_t col = 0; col < Board::Columns(); ++col) {
            if (game.GetPlayer(col, row).has_value())
                ++availableMoves;
        }
    }
    EXPECT_EQ(availableMoves, 1u);
}

TEST(GameTests, RequireThat_GetGameStatus_ReturnsInProgress_WhenBoardIsEmpty) {
    Game game{Player::X};

    EXPECT_EQ(game.GetGameStatus(Player::X), GameStatus::InProgress);
    EXPECT_EQ(game.GetGameStatus(Player::O), GameStatus::InProgress);
}

TEST(GameTests, RequireThat_GetGameStatus_ReturnsWin_WhenPlayerWon) {
    Game game{Player::X};
    game.MakeMove(0u, 0u); // X
    game.MakeMove(0u, 1u); // O
    game.MakeMove(1u, 0u); // X
    game.MakeMove(1u, 1u); // O
    game.MakeMove(2u, 0u); // X

    EXPECT_EQ(game.GetGameStatus(Player::X), GameStatus::Win);
}
