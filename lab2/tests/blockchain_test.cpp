#include "gtest/gtest.h"
#include "../blockchain.hpp"
#include <sstream>

class ConcurrentBlockChainTest : public ::testing::Test {
protected:
    std::stringstream output;
    ConcurrentBlockChain* chain;

    void SetUp() override {
        // 3 цепочки, макс. 2 транзакции
        chain = new ConcurrentBlockChain(output, 3, 2);
    }

    void TearDown() override {
        delete chain;
    }
};

TEST_F(ConcurrentBlockChainTest, WriteAddsToRandomChain) {
    chain->write(123, 100, 150);
    chain->write(456, 200, 180);
    for(int i = 0; i < 3; i++) {
        chain->archive(i);
    }

    // Проверяем, что обе записи попали в output (через archive)
    std::string result = output.str();
    EXPECT_NE(result.find(">123:100:150"), std::string::npos);
    EXPECT_NE(result.find(">456:200:180"), std::string::npos);
}

TEST_F(ConcurrentBlockChainTest, ArchiveCalledWhenMaxReached) {
    // Заполняем цепочку 0 до предела
    chain->write(1, 0, 10);  // в цепочку 0
    chain->write(2, 10, 20); // в цепочку 0 → должно вызвать archive
    for(int i = 0; i < 3; i++) {
        chain->archive(i);
    }

    std::string result = output.str();
    EXPECT_NE(result.find("archiving chain 0"), std::string::npos);
    EXPECT_NE(result.find(">1:0:10"), std::string::npos);
    EXPECT_NE(result.find(">2:10:20"), std::string::npos);
}

TEST_F(ConcurrentBlockChainTest, MultipleChainsWorkIndependently) {
    chain->write(10, 0, 5);
    chain->write(20, 5, 15);
    chain->write(30, 15, 25);
    chain->write(40, 10, 20);
    chain->write(50, 20, 30);
    chain->write(60, 25, 15);
    chain->write(1, 2, 5); // Гарантированно вызовет archive

    std::string result = output.str();
    // Все четыре записи должны быть в output
    EXPECT_NE(result.find(">10:0:5"), std::string::npos);
    EXPECT_NE(result.find(">20:5:15"), std::string::npos);
}
