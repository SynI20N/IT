#include "bank_account.hpp"
#include <stdexcept>

extern std::random_device rand_dev;
extern std::mt19937 mt;

BankAccount::BankAccount(int amount, ConcurrentBlockChain& logger) 
: amount_(amount), logger_(logger) {
    id_ = std::uniform_int_distribution<int>(1000000, 9000000)(mt);
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
    int money = std::uniform_int_distribution<int>(10, 50)(mt);
    add(money);
}

void BankAccount::take_random() {
    int money = std::uniform_int_distribution<int>(10, 50)(mt);
    take(money);
}
