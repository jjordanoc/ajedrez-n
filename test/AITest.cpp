//
// Created by renato on 6/16/2022.
//

#include "iostream"
#include "gtest/gtest.h"
#include "../src/backend/game/AI.h"
#include "../src/backend/game/Engine.h"


class AITest : public ::testing::Test {
protected:
    chess::Board board;
    void SetUp() override {
        std::cout << "Set up" << std::endl;
        auto &engine = chess::Engine::getInstance();
        engine.initBoard();
        board = engine.getBoard();
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }
};


TEST_F(AITest, minimax){
    std::cout << chess::minimax(board, true, 2) << std::endl;
}


// TEST_F allows you to access
//TEST_F(IATest, CanMovePiece) {
//    ASSERT_EQ(1, 1);
//}
//
//TEST_F(IATest, FailTest) {
//    ASSERT_EQ(1, 0);
//}