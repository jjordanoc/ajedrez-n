//
// Created by renato on 6/21/2022.
//

#include "../src/backend/game/Board.h"
#include "../src/backend/game/Engine.h"
#include "iostream"
#include "gtest/gtest.h"

class BoardTest : public ::testing::Test {
protected:
    chess::Board board;
    void SetUp() override {
        auto &engine = chess::Engine::getInstance();
        engine.initBoard(0);
        board = engine.getBoard();
    }

    void TearDown() override {
    }
};


TEST_F(BoardTest, evaluateInitialBoard) {
    ASSERT_EQ(board.evaluation(), 0);
}

TEST_F(BoardTest, evaluateCheckMate) {
    board.movePiece(6, 5, 5, 5);
    board.movePiece(1, 4, 3, 4);
    board.movePiece(6, 6, 4, 6);
    board.movePiece(0, 3, 4, 7);
    ASSERT_EQ(board.evaluation(), MIN_SCORE);
}