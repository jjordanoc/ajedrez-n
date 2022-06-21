//
// Created by renato on 6/21/2022.
//

#include "iostream"
#include "gtest/gtest.h"
#include "../src/backend/game/Board.h"
#include "../src/backend/game/Engine.h"

class BoardTest : public ::testing::Test {
protected:
    chess::Board board;
    void SetUp() override {
        std::cout << "Set up" << std::endl;
        auto engine = chess::Engine::get_instance();
        engine->initBoard();
        board = engine->getBoard();
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
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
    ASSERT_EQ(board.evaluation(), -std::numeric_limits<double>::infinity());
}