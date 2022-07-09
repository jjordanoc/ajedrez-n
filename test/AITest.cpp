//
// Created by renato on 6/16/2022.
//

#include "../src/backend/game/AI.h"
#include "../src/backend/game/Engine.h"
#include "iostream"
#include "gtest/gtest.h"


class AITest : public ::testing::Test {
protected:
    chess::Engine &engine = chess::Engine::getInstance();
    chess::AI AI = chess::AI();
    void SetUp() override {
        std::cout << "Set up" << std::endl;
        engine.initBoard();
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }
};


//TEST_F(AITest, minimaxMaxPlayer) {
//    chess::AI AI = chess::AI();
//    std::cout << AI.minimax(engine.getBoard(), true, 5) << std::endl;
//}
//
//TEST_F(AITest, minimaxMinPlayer) {
//    chess::AI AI = chess::AI();
//    std::cout << AI.minimax(engine.getBoard(), false, 5) << std::endl;
//}
//
//TEST_F(AITest, trivialCheckMateMaxPlayer) {
//    chess::AI AI = chess::AI();
//    engine.getBoard().putPiece("King", chess::WHITE, 7, 4);
//    engine.getBoard().putPiece("King", chess::BLACK, 0, 4);
//
//    engine.getBoard().putPiece("Queen", chess::WHITE, 7, 3);
//
//    engine.getBoard().putPiece("Rook", chess::WHITE, 7, 0);
//    engine.getBoard().putPiece("Rook", chess::WHITE, 7, 7);
//
//    engine.getBoard().putPiece("Knight", chess::WHITE, 7, 1);
//    engine.getBoard().putPiece("Knight", chess::WHITE, 7, 6);
//
//    engine.getBoard().putPiece("Bishop", chess::WHITE, 7, 2);
//    engine.getBoard().putPiece("Bishop", chess::WHITE, 7, 5);
//
//    for (int i = 0; i < BOARD_SIZE; i++) {
//        engine.getBoard().putPiece("Pawn", chess::WHITE, 6, i);
//    }
//
//    engine.getBoard().print();
//    std::cout << AI.minimax(engine.getBoard(), true, 5) << std::endl;
//}

TEST_F(AITest, TestGame) {

}


// TEST_F allows you to access
//TEST_F(IATest, CanMovePiece) {
//    ASSERT_EQ(1, 1);
//}
//
//TEST_F(IATest, FailTest) {
//    ASSERT_EQ(1, 0);
//}