#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include "blockchain.hpp"
#include <random>

/**
 * @brief Банковский аккаунт клиента
 */
class BankAccount {
public:
    BankAccount(int amount, ConcurrentBlockChain& logger);
    void add(int money);
    void take(int money);
    void add_random();
    void take_random();
    long long get_amount() const;
    int get_id() const;
private:
    long long amount_;
    ConcurrentBlockChain& logger_;
    int id_;
};

#endif