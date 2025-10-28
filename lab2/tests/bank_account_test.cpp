#include "gtest/gtest.h"
#include "../bank_account.hpp"
#include "mock_blockchain.hpp"

class BankAccountTest : public ::testing::Test {
protected:
    MockBlockChain mockLogger;
    BankAccount* account;

    void SetUp() override {
        account = new BankAccount(100, mockLogger);
    }

    void TearDown() override {
        delete account;
    }
};

TEST_F(BankAccountTest, ConstructorSetsInitialAmountAndId) {
    EXPECT_EQ(account->get_amount(), 100);
    EXPECT_GE(account->get_id(), 1000000);
    EXPECT_LE(account->get_id(), 9000000);
}

TEST_F(BankAccountTest, AddIncreasesAmountAndLogs) {
    account->add(25);
    EXPECT_EQ(account->get_amount(), 125);
    ASSERT_EQ(mockLogger.getLogSize(), 1u);
    auto entry = mockLogger.getLastEntry();
    EXPECT_EQ(entry.id, account->get_id());
    EXPECT_EQ(entry.prev, 100);
    EXPECT_EQ(entry.curr, 125);
}

TEST_F(BankAccountTest, TakeDecreasesAmountAndLogs) {
    account->take(30);
    EXPECT_EQ(account->get_amount(), 70);
    ASSERT_EQ(mockLogger.getLogSize(), 1u);
    auto entry = mockLogger.getLastEntry();
    EXPECT_EQ(entry.id, account->get_id());
    EXPECT_EQ(entry.prev, 100);
    EXPECT_EQ(entry.curr, 70);
}

TEST_F(BankAccountTest, TakeThrowsIfInsufficientFunds) {
    EXPECT_THROW(account->take(150), std::runtime_error);
    EXPECT_EQ(account->get_amount(), 100);  // не изменилось
    EXPECT_EQ(mockLogger.getLogSize(), 0u);  // нет записи
}

TEST_F(BankAccountTest, AddRandomAddsWithinRange) {
    long long initial = account->get_amount();
    account->add_random();
    long long final = account->get_amount();
    EXPECT_GE(final, initial + 10);
    EXPECT_LE(final, initial + 50);
    EXPECT_EQ(mockLogger.getLogSize(), 1u);
}

TEST_F(BankAccountTest, TakeRandomTakesWithinRange) {
    // Гарантируем, что денег хватит
    if (account->get_amount() < 50) account->add(100);
    long long initial = account->get_amount();
    account->take_random();
    long long final = account->get_amount();
    EXPECT_GE(final, initial - 50);
    EXPECT_LE(final, initial - 10);
    EXPECT_EQ(mockLogger.getLogSize(), 1u);
}
