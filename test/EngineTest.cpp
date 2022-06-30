#include "iostream"
#include "gtest/gtest.h"
#include "../src/backend/game/Engine.h"



class EngineTest : public ::testing::Test {
protected:
    chess::Engine *engine;
    void SetUp() override {
//        engine = chess::Engine::getInstance();
//        engine->initBoard();
    }

    void TearDown() override {
        // delete engine;
    }
};


// TEST_F allows you to access
TEST_F(EngineTest, PLY_0) {
//    auto result = engine->Perft(0);
//    EXPECT_EQ(result, 1);
}

TEST_F(EngineTest, PLY_1) {
//    auto result = engine->Perft(1);
//    EXPECT_EQ(result, 20);
}

TEST_F(EngineTest, PLY_2) {
//    auto result = engine->Perft(2);
//    EXPECT_EQ(result, 400);
}

TEST_F(EngineTest, PLY_3) {
//    auto result = engine->Perft(3);
//    EXPECT_EQ(result, 8902);
}
