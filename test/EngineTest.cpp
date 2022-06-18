#include "iostream"
#include "gtest/gtest.h"
#include "../src/backend/game/Engine.h"



class EngineTest : public ::testing::Test {
protected:
    chess::Engine *engine;
    void SetUp() override {
        engine = chess::Engine::get_instance();
        engine->initBoard();
    }

    void TearDown() override {
        delete engine;
    }
};


// TEST_F allows you to access
TEST_F(EngineTest, PLY_1) {
    auto result = engine->Perft(0);
    EXPECT_EQ(result, 1);
}
