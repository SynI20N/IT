#include "bank_account.hpp"
#include <random>
#include <stdexcept>

std::mt19937 mt2(rand());

BankAccount::BankAccount(int amount, ConcurrentBlockChain& logger) 
: amount_(amount), logger_(logger) {
    id_ = std::uniform_int_distribution<int>(1000000, 10000000)(mt2);
}

void BankAccount::add(int money) {
    long long prev = amount_;
    amount_ += money;
    logger_.write(id_, prev, amount_);
}

void BankAccount::take(int money) {
    long long prev = amount_;
    if(amount_ < money) {
        throw std::runtime_error(
            "not enough money, id: " + std::to_string(id_)
        );
    }
    amount_ -= money;
    logger_.write(id_, prev, amount_);
}

void BankAccount::add_random() {
    int money = std::uniform_int_distribution<int>(10, 50)(mt2);
    add(money);
}

void BankAccount::take_random() {
    int money = std::uniform_int_distribution<int>(10, 50)(mt2);
    take(money);
}
