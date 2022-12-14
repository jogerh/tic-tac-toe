#include <Board.h>
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

