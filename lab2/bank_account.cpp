#include "bank_account.hpp"
#include <random>
#include <stdexcept>

BankAccount::BankAccount(int amount, ConcurrentBlockChain& logger) 
: amount_(amount), logger_(logger) {
    if(mt_ == nullptr) {
        std::random_device randD;
        mt_ = new std::mt19937(randD);
    }
    std::uniform_int_distribution <int> range(10e8, 10e9);
    id_ = range(mt_);
}

BankAccount::~BankAccount() {
    delete mt_;
}

void BankAccount::Add(int money) {
    long long prev = amount_;
    amount_ += money;

    logger_.Write(id_, prev, amount_);
}

void BankAccount::Take(int money) {
    long long prev = amount_;
    if(amount_ < money) {
        throw std::runtime_error(
            "not enough money, id: " + std::to_string(id_)
        );
    }
    amount_ -= money;

    logger_.Write(id_, prev, amount_);
}