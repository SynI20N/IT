#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include "blockchain.hpp"
#include <random>

class BankAccount {
public:
    BankAccount(int amount, ConcurrentBlockChain& logger);
    void add(int money);
    void take(int money);
    void add_random();
    void take_random();
private:
    long long amount_;
    ConcurrentBlockChain& logger_;
    int id_;
};

#endif