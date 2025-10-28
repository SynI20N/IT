#include "gtest/gtest.h"
#include "../bank.hpp"
#include "mock_blockchain.hpp"

class BankTest : public ::testing::Test {
protected:
    MockBlockChain mockLogger;
    Bank* bank;

    void SetUp() override {
        bank = new Bank(10, mockLogger);  // 10 счетов по 100 руб.
    }

    void TearDown() override {
        delete bank;
    }
};

TEST_F(BankTest, ConstructorCreatesAccountsWithCorrectAmount) {
    EXPECT_EQ(bank->get_accounts_count(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(bank->get_account(i).get_amount(), 100);
    }
}

TEST_F(BankTest, ProcessAccountsAppliesRandomOperations) {
    bank->process_accounts(0, 3);  // обрабатываем первые 3 счёта

    for (int i = 0; i < 3; ++i) {
        long long amount = bank->get_account(i).get_amount();
        // После add_random/take_random сумма должна быть в разумных пределах
        EXPECT_GE(amount, 50);   // минимум: 100 − 50
        EXPECT_LE(amount, 150);  // максимум: 100 + 50
    }
    EXPECT_GE(mockLogger.getLogSize(), 3u);  // минимум 3 операции
}

TEST_F(BankTest, SimulateUsesMultipleThreads) {
    bank->simulate(2);  // 2 потока

    // Все 10 счетов должны быть обработаны
    EXPECT_EQ(mockLogger.getLogSize(), 10u);

    // Проверяем, что баланс каждого счёта изменился
    for (int i = 0; i < 10; ++i) {
        long long amount = bank->get_account(i).get_amount();
        EXPECT_NE(amount, 100);  // должен измениться после операции
    }
}