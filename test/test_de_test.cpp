//
// Created by renato on 6/16/2022.
//

#include "gtest/gtest.h"
#include "iostream"

class IATest : public ::testing::Test{
protected:
    void SetUp() override {
        std::cout << "Set up" << std::endl;
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }
};

// TEST_F allows you to access
TEST_F(IATest, CanMovePiece){
    ASSERT_EQ(1, 1);
}

TEST_F(IATest, FailTest){
    ASSERT_EQ(1, 0);
}